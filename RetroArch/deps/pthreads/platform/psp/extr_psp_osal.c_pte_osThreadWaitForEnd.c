#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_osThreadHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;
struct TYPE_8__ {int /*<<< orphan*/  cancelSem; } ;
typedef  TYPE_1__ pspThreadData ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_10__ {scalar_t__ currentCount; } ;
struct TYPE_9__ {int size; scalar_t__ status; } ;
typedef  scalar_t__ SceUID ;
typedef  TYPE_2__ SceKernelThreadRunStatus ;
typedef  TYPE_3__ SceKernelSemaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  POLLING_DELAY_IN_us ; 
 scalar_t__ PSP_THREAD_STOPPED ; 
 int /*<<< orphan*/  PTE_OS_GENERAL_FAILURE ; 
 int /*<<< orphan*/  PTE_OS_INTERRUPTED ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 scalar_t__ SCE_KERNEL_ERROR_OK ; 
 TYPE_1__* getThreadData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sceKernelDelayThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceKernelGetThreadId () ; 
 scalar_t__ sceKernelReferSemaStatus (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sceKernelReferThreadRunStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 

pte_osResult pte_osThreadWaitForEnd(pte_osThreadHandle threadHandle)
{
   pte_osResult result;
   pspThreadData *pThreadData = getThreadData(sceKernelGetThreadId());

   while (1)
   {
      SceKernelThreadRunStatus info;

      /* Poll task to see if it has ended */
      memset(&info,0,sizeof(info));
      info.size = sizeof(info);
      sceKernelReferThreadRunStatus(threadHandle, &info);      

      if (info.status == PSP_THREAD_STOPPED)
      {
         /* Thread has ended */
         result = PTE_OS_OK;
         break;
      }
      else
      {
         SceKernelSemaInfo semInfo;

         if (pThreadData != NULL)
         {
            SceUID osResult;

            osResult = sceKernelReferSemaStatus(pThreadData->cancelSem, &semInfo);

            if (osResult == SCE_KERNEL_ERROR_OK)
            {
               if (semInfo.currentCount > 0)
               {
                  result = PTE_OS_INTERRUPTED;
                  break;
               }
               /* Nothing found and not timed out yet; let's yield so we're not
                * in busy loop.
                */
               else
                  sceKernelDelayThread(POLLING_DELAY_IN_us);
            }
            else
            {
               result = PTE_OS_GENERAL_FAILURE;
               break;
            }
         }
      }
   }


   return result;
}