#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  threadName ;
typedef  scalar_t__ pte_osThreadHandle ;
typedef  int /*<<< orphan*/  pte_osThreadEntryPoint ;
typedef  int /*<<< orphan*/  pte_osResult ;
struct TYPE_4__ {int /*<<< orphan*/  cancelSem; void* argv; int /*<<< orphan*/  entryPoint; } ;
typedef  TYPE_1__ pspThreadData ;
typedef  int /*<<< orphan*/  cancelSemName ;
typedef  scalar_t__ SceUID ;

/* Variables and functions */
 int DEFAULT_STACK_SIZE_BYTES ; 
 int /*<<< orphan*/  MAX_PSP_UID ; 
 int /*<<< orphan*/  PSP_DEBUG (char*) ; 
 int /*<<< orphan*/  PTE_OS_GENERAL_FAILURE ; 
 int /*<<< orphan*/  PTE_OS_NO_RESOURCES ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 scalar_t__ SCE_KERNEL_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pspStubThreadEntry ; 
 int /*<<< orphan*/  pteTlsSetValue (void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pteTlsThreadDestroy (void*) ; 
 void* pteTlsThreadInit () ; 
 int /*<<< orphan*/  sceKernelCreateSema (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sceKernelCreateThread (char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  threadDataKey ; 

pte_osResult pte_osThreadCreate(pte_osThreadEntryPoint entryPoint,
                                int stackSize,
                                int initialPriority,
                                void *argv,
                                pte_osThreadHandle* ppte_osThreadHandle)
{
   char threadName[64];
   char cancelSemName[64];
   static int threadNum = 1;
   int pspAttr;
   void *pTls;
   SceUID threadId;
   pte_osResult result;
   pspThreadData *pThreadData;

   if (threadNum++ > MAX_PSP_UID)
      threadNum = 0;

   /* Make sure that the stack we're going to allocate is big enough */
   if (stackSize < DEFAULT_STACK_SIZE_BYTES)
      stackSize = DEFAULT_STACK_SIZE_BYTES;

   /* Allocate TLS structure for this thread. */
   pTls = pteTlsThreadInit();
   if (pTls == NULL)
   {
      PSP_DEBUG("pteTlsThreadInit: PTE_OS_NO_RESOURCES\n");
      result = PTE_OS_NO_RESOURCES;
      goto FAIL0;
   }

   /* Allocate some memory for our per-thread control data.  We use this for:
    * 1. Entry point and parameters for the user thread's main function.
    * 2. Semaphore used for thread cancellation.
    */
   pThreadData = (pspThreadData *) malloc(sizeof(pspThreadData));

   if (pThreadData == NULL)
   {
      pteTlsThreadDestroy(pTls);

      PSP_DEBUG("malloc(pspThreadData): PTE_OS_NO_RESOURCES\n");
      result = PTE_OS_NO_RESOURCES;
      goto FAIL0;
   }

   /* Save a pointer to our per-thread control data as a TLS value */
   pteTlsSetValue(pTls, threadDataKey, pThreadData);

   pThreadData->entryPoint = entryPoint;
   pThreadData->argv = argv;

   /* Create a semaphore used to cancel threads */
   snprintf(cancelSemName, sizeof(cancelSemName), "pthread_cancelSem%04d", threadNum);

   pThreadData->cancelSem = sceKernelCreateSema(cancelSemName,
         0,          /* attributes (default) */
         0,          /* initial value        */
         255,        /* maximum value        */
         0);         /* options (default)    */


   /* In order to emulate TLS functionality, we append the address of the TLS structure that we
    * allocated above to the thread's name.  To set or get TLS values for this thread, the user
    * needs to get the name of the thread from the OS and then parse the name to extract
    * a pointer to the TLS structure.
    */
   snprintf(threadName, sizeof(threadName), "pthread%04d__%x", threadNum, (unsigned int) pTls);

   pspAttr = 0;

#if 0
   printf("%s %p %d %d %d\n",threadName, pspStubThreadEntry, initialPriority, stackSize, pspAttr);
#endif
   threadId = sceKernelCreateThread(threadName,
         pspStubThreadEntry,
         initialPriority,
         stackSize,
         pspAttr,
         NULL);

   if (threadId == (SceUID) SCE_KERNEL_ERROR_NO_MEMORY)
   {
      free(pThreadData);
      pteTlsThreadDestroy(pTls);

      PSP_DEBUG("sceKernelCreateThread: PTE_OS_NO_RESOURCES\n");
      result =  PTE_OS_NO_RESOURCES;
   }
   else if (threadId < 0)
   {
      free(pThreadData);
      pteTlsThreadDestroy(pTls);

      PSP_DEBUG("sceKernelCreateThread: PTE_OS_GENERAL_FAILURE\n");
      result = PTE_OS_GENERAL_FAILURE;
   }
   else
   {
      *ppte_osThreadHandle = threadId;
      result = PTE_OS_OK;
   }

FAIL0:
   return result;
}