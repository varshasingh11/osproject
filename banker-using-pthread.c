#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define RESOURCES 4
#define PROCESSES 5
	int i = 0;
	int j = 0;
pthread_mutex_t mutex;
	int avail [RESOURCES]={1,5,2,0};
	int allocmatrix [PROCESSES][RESOURCES]={{0,1,1,0,0},{0,0,3,6,0},{1,0,5,3,1},{2,0,4,2,4}}; 
	int MaxMatrix [PROCESSES][RESOURCES]={{0,1,2,0,0},{0,7,3,6,6},{1,5,5,5,5},{2,0,6,2,6}}; 
	int NeedMatrix [PROCESSES][RESOURCES];
	int init [RESOURCES];

void *pros(void* prosID)
{
            int pID = *(int*)prosID;
int c=0;
            while(c<3)
            {
                        //generate random requests
                        sleep(1);
                        int request[RESOURCES];

                       
                        pthread_mutex_lock(&mutex);

                        //NeedMatrix vector ko initialize karna
                        for(i = 0; i < RESOURCES; i++)
                        {
                                    if(NeedMatrix[pID][i] != 0)
                                    {
                                     request[i] = rand() % NeedMatrix[pID][i];
                                    }
                                    else
                                    {
                                                request[i] = 0;
                                    }
                        }


printf("Process %d is requiring resources:\n",pID);
                        printReqOrRelVector(request);

                        getRes(pID,request);

pthread_mutex_unlock(&mutex);
           
//random release vector gernerate karne ke liye            
sleep(1);
int releaseVector[RESOURCES];
                       
pthread_mutex_lock(&mutex);

//release vector ko initialize karna
for(i = 0; i < RESOURCES; i++)
{
if(allocmatrix[pID][i] != 0)
            {
                        releaseVector[i] = rand() % allocmatrix[pID][i];
            }
            else
            {
                        releaseVector[i] = 0;
            }
}


printf("Process %d is releasing resources:\n",pID);
                        printReqOrRelVector(releaseVector);
                       
relRes(pID,releaseVector);
//unlock
pthread_mutex_unlock(&mutex);

c++;
            }
}

int getRes(int pID,int request[])
{
            if (casegreaterthanneed(pID,request) == -1)
            {
                        printf("Resources are surplus\n");
                        return -1;
            }
            printf("Please Wait While resources are being allocated...\n");

            if(enoughtoalloccase(request) == -1)
            {
                        printf("Resources Fall Short.\n");
                        return -1;
            }

        
            for (i = 0; i < RESOURCES; ++i)
            {
                        NeedMatrix[pID][i] -= request[i];
                        allocmatrix[pID][i] += request[i];
                        avail[i] -= request[i];
            }
            printf("Verifying the state safety **********\n");
           
            if (safemodecase() == 0)
            {
                        printf("\nx========================x\n|Safe Mode. Resources Allocated|\nx=========================x\n ");
                        exit(1);
                        return 0;
            }
            else
            {           
                        printf("\nx=====================x\n|State is not safe.          |\nx=====================x\n");
                       
                   exit(1);
                        return -1;
            }
}

int relRes(int pID,int releaseVector[])
{          

            if(caseengoughtorel(pID,releaseVector) == -1)
            {
                        printf("Resources Fall Short.\n");
                        return -1;
            }
            for(i = 0; i < RESOURCES; i++)
            {
                        allocmatrix[pID][i] -= releaseVector[i];
                        NeedMatrix[pID][i] += releaseVector[i];
                        avail[i] += releaseVector[i];
            }
            printf("Released.\nMatrix Available:\n");
            showavail();
            printf("Matrix Allocated:\n");
            Showalloc();
            printf("Matrix Needed:\n");
            ShowNeed();
            return 0;
}


int caseengoughtorel(int pID,int releaseVector[])
{          
            for (i = 0; i < RESOURCES; ++i)
            {
                        if (releaseVector[i] <= allocmatrix[pID][i])
                                    { continue; }
                        else
                                    { return -1;}
            }
            return 0;
}

int casegreaterthanneed(int pID,int request[])
{

            for (i = 0; i < RESOURCES; ++i)
            {
                        if (request[i] <= NeedMatrix[pID][i])
                                    {  continue; }
                        else
                        { return -1; }
            }
            return 0;
}

int enoughtoalloccase(int request[])
{

            for (i = 0; i < RESOURCES; ++i)
            {
                        if (request[i] <= avail[i])
                                    { continue; }
                        else
                        { return -1; }
            }
            return 0;
}

void ShowNeed()
{
            for (i = 0; i < PROCESSES; ++i)
            {
                        printf("{ ");
                        for (j = 0; j < RESOURCES; ++j)
                        {
                                    printf("%d, ", NeedMatrix[i][j]);
                        }
                        printf("}\n");
            }
            return;
}

void Showalloc()
{
            for (i = 0; i < PROCESSES; ++i)
            {
                        printf("{ ");
                        for (j = 0; j < RESOURCES; ++j)
                        {
                                    printf("%d, ", allocmatrix[i][j]);
                        }
                        printf("}\n");
            }
            return;
}

void showavail()
{
            for (i = 0; i < RESOURCES; ++i)
            {
                        printf("%d, ",avail[i]);
            }
            printf("\n");
            return;
}


void printReqOrRelVector(int vec[])
{
            for (i = 0; i < RESOURCES; ++i)
            {
                        printf("%d, ",vec[i]);
            }
            printf("\n");
            return;
}


int safemodecase()
{
            int finish[PROCESSES] = {0};

            //inicialize Work=Available
            int work[RESOURCES];

            for(i = 0; i < RESOURCES; i++)
            {
                       work[i] = avail[i];
            }

            int k;
            for(i = 0; i < PROCESSES; i++)
            {
                        if (finish[i] == 0)
                        {
                                    for(j = 0; j < RESOURCES; j++)
                                    {
                                                if(NeedMatrix[i][j] <= work[j])
                                                {
                                                            
	if(j==RESOURCES-1)                                                                                                            {
                                                                        finish[i] = 1;
                                                            for (k = 0; k < RESOURCES; ++k)
                                                                        {
                                                                                    work[k] += allocmatrix[i][k];
                                                                                 
                                                                        }
                                                                       
                                   
i = -1;
break;
            }
else
                        { continue; }
}
else
                        { break; }
}
}
else
{  continue; }
}
           
            for(i = 0; i < PROCESSES; i++)
            {
                        if (finish[i] == 0)
                        {
                                    
                                    return -1;
                        }
                        else
                        { continue; }
            }
            
            return 0;
}

int main()
{           

            //NeedMatrix matrix ko initialize karna
            for (i = 0; i < PROCESSES; ++i)
            {
                        for (j = 0; j < RESOURCES; ++j)
                        {
                                    NeedMatrix[i][j] = MaxMatrix[i][j] - allocmatrix[i][j];
                        }
            }

            printf("Available Vector is:\n");
            showavail();

            printf("Allocation Matrix is:\n");
            Showalloc();

            printf("Need Matrix is:\n");
            ShowNeed();

            pthread_mutex_init(&mutex,NULL);
            pthread_attr_t attrDefault;
            pthread_attr_init(&attrDefault);
            pthread_t *tid = malloc(sizeof(pthread_t) * PROCESSES);

            int *pid = malloc(sizeof(int) * PROCESSES); // process ID 

            //initialize pid and create pthreads
            for(i = 0; i < PROCESSES; i++)
            {
                        *(pid + i) = i;
                        pthread_create((tid+i), &attrDefault, pros, (pid+i));
            }

            //join threads
            for(i = 0; i < PROCESSES; i++)
            {
                        pthread_join(*(tid+i),NULL);
            }
            return 0;
}

