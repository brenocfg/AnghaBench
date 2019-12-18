#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pte_osResult ;
struct TYPE_3__ {int /*<<< orphan*/  cancelSem; } ;
typedef  TYPE_1__ pspThreadData ;
typedef  int /*<<< orphan*/  cancelSemName ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_MAX_TLS ; 
 scalar_t__ PTE_OS_NO_RESOURCES ; 
 scalar_t__ PTE_OS_OK ; 
 int /*<<< orphan*/  globalTls ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ pteTlsAlloc (int /*<<< orphan*/ *) ; 
 scalar_t__ pteTlsGlobalInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pteTlsSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pteTlsThreadInit () ; 
 int /*<<< orphan*/  sceKernelCreateSema (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  threadDataKey ; 

pte_osResult pte_osInit(void)
{
   pte_osResult result;
   pspThreadData *pThreadData;
   char cancelSemName[64];

   /* Allocate and initialize TLS support */
   result = pteTlsGlobalInit(PSP_MAX_TLS);

   if (result == PTE_OS_OK)
   {
      /* Allocate a key that we use to store control information (e.g. cancellation semaphore) per thread */
      result = pteTlsAlloc(&threadDataKey);

      if (result == PTE_OS_OK)
      {

         /* Initialize the structure used to emulate TLS for 
          * non-POSIX threads 
          */
         globalTls = pteTlsThreadInit();

         /* Also create a "thread data" structure for a single non-POSIX thread. */

         /* Allocate some memory for our per-thread control data.  We use this for:
          * 1. Entry point and parameters for the user thread's main function.
          * 2. Semaphore used for thread cancellation.
          */
         pThreadData = (pspThreadData *) malloc(sizeof(pspThreadData));

         if (pThreadData == NULL)
         {
            result = PTE_OS_NO_RESOURCES;
         }
         else
         {

            /* Save a pointer to our per-thread control data as a TLS value */
            pteTlsSetValue(globalTls, threadDataKey, pThreadData);

            /* Create a semaphore used to cancel threads */
            snprintf(cancelSemName, sizeof(cancelSemName), "pthread_cancelSemGlobal");

            pThreadData->cancelSem = sceKernelCreateSema(cancelSemName,
                  0,          /* attributes (default) */
                  0,          /* initial value        */
                  255,        /* maximum value        */
                  0);         /* options (default)    */
            result = PTE_OS_OK;
         }
      }
   }

   return result;
}