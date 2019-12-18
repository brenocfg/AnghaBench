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
typedef  int /*<<< orphan*/  pte_osThreadHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;
struct TYPE_3__ {int /*<<< orphan*/  cancelSem; } ;
typedef  TYPE_1__ pspThreadData ;
typedef  scalar_t__ SceUID ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_GENERAL_FAILURE ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 scalar_t__ SCE_KERNEL_ERROR_OK ; 
 TYPE_1__* getThreadData (int /*<<< orphan*/ ) ; 
 scalar_t__ sceKernelSignalSema (int /*<<< orphan*/ ,int) ; 

pte_osResult pte_osThreadCancel(pte_osThreadHandle threadHandle)
{
   pspThreadData *pThreadData = getThreadData(threadHandle);
   SceUID osResult            = sceKernelSignalSema(pThreadData->cancelSem, 1);

   if (osResult == SCE_KERNEL_ERROR_OK)
      return PTE_OS_OK;

   return PTE_OS_GENERAL_FAILURE;
}