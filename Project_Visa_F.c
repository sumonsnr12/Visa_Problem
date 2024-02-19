#include <stdio.h>
#include<stdlib.h>

        


struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];       // How many nodes will be connected with one node.
};

int path = 1;
// checking Visa

void findVisa(int *list,int lcount,int arr[],int total_v){
    int test = 0;
    for (int i=0;i<total_v;i++)
    {
        for (int  j = 0; j < lcount; j++)
        {
            if (arr[i] ==  list[j])  
            {
                test++;
                break;
            }
            
        }
        
    }
    if (test == lcount-1)
    {
        printf("Path-%d : ",path);
        path++;
        for (int  i = 0; i < lcount; i++)
        {
            printf("%d -> ",list[i]);
        }
        printf("\n");
    }
    
    
    
}
int addNode (struct Node * p, int nid, int count)
{
    int i =0, ncount = count;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int count)
{
    int i =0, index;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].adjcount = c+1;
           
            break;
        }
    }
}

int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


void findpath (struct Node * p, int count, int start, int end, int * list, int lcount,int arr[],int total_V)
{
    int index = 0, i=0;
   
   
    //check if list contains the end node
    if (list[lcount-1] == end)
    {
         findVisa(list,lcount,arr,total_V);
        return;
    }
   
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == start) { index = i; break; }
    }
   
    for (i=0;i<p[index].adjcount;i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            lcount++;
           
            findpath (p, count, p[index].adjs[i], end, list, lcount,arr,total_V);
            lcount--;
        }

    }

    
}


int main() {
   
    struct Node nodes[50]; 
    int nodecount = 0;
    int n1=0, n2=0, c = 0;
   
    for(int i = 1;;i+=2)
    {
    
        printf ("n%d, n%d ? ",i,i+1);
        scanf("%d %d", &n1, &n2);
        if (n1 == -9 || n2 == -9) {break;}
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);
       
        addAdjacent (&nodes[0], n1, n2, nodecount);
        addAdjacent (&nodes[0], n2, n1, nodecount);
    }
   
    int start, end;
    int arr[10];
    int total_V = 0;
    printf("Enter the visa that You have: ");
    for (int i = 0;; i++)
    {
        scanf("%d",&arr[i]);
        if(arr[i]==-9){
            break;
        }
        total_V++;
    }
    
    printf ("Start Position & end position ? ");
    scanf ("%d %d", &start, &end);

    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    int pass = 0;
    for (int i = 0; i < total_V; i++)
    {
        if (end==arr[i])
        {
            pass = 1;
            break;
        }
        
    }
    
    if(pass == 1){
        findpath (nodes, nodecount, start, end, list, lcount,arr,total_V);
    }else
    {
        printf("Its impossible to reach final destination.Because user haven't visa for destination Country.");
    }
    

    return 0;
}