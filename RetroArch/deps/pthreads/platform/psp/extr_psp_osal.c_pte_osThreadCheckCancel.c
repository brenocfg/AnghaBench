#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pte_osThreadHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;
struct TYPE_5__ {int /*<<< orphan*/  cancelSem; } ;
typedef  TYPE_1__ pspThreadData ;
struct TYPE_6__ {scalar_t__ currentCount; } ;
typedef  scalar_t__ SceUID ;
typedef  TYPE_2__ SceKernelSemaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_GENERAL_FAILURE ; 
 int /*<<< orphan*/  PTE_OS_INTERRUPTED ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 scalar_t__ SCE_KERNEL_ERROR_OK ; 
 TYPE_1__* getThreadData (int /*<<< orphan*/ ) ; 
 scalar_t__ sceKernelReferSemaStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 

pte_osResult pte_osThreadCheckCancel(pte_osThreadHandle threadHandle)
{
   SceKernelSemaInfo semInfo;
   SceUID osResult;
   pte_osResult result;
   pspThreadData *pThreadData = getThreadData(threadHandle);

   if (pThreadData != NULL)
   {
      osResult = sceKernelReferSemaStatus(pThreadData->cancelSem, &semInfo);

      if (osResult == SCE_KERNEL_ERROR_OK)
      {
         if (semInfo.currentCount > 0)
            result = PTE_OS_INTERRUPTED;
         else
            result = PTE_OS_OK;
      }
      /* sceKernelReferSemaStatus returned an error */
      else
         result = PTE_OS_GENERAL_FAILURE;
   }
   /* For some reason, we couldn't get thread data */
   else
      result = PTE_OS_GENERAL_FAILURE;

   return result;
}