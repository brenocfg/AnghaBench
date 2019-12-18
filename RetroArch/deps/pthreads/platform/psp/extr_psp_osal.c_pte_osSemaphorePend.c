#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pte_osSemaphoreHandle ;
typedef  int /*<<< orphan*/  pte_osResult ;
typedef  scalar_t__ SceUInt ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_GENERAL_FAILURE ; 
 int /*<<< orphan*/  PTE_OS_OK ; 
 int /*<<< orphan*/  PTE_OS_TIMEOUT ; 
 scalar_t__ SCE_KERNEL_ERROR_OK ; 
 scalar_t__ SCE_KERNEL_ERROR_WAIT_TIMEOUT ; 
 scalar_t__ sceKernelWaitSema (int /*<<< orphan*/ ,int,unsigned int*) ; 

pte_osResult pte_osSemaphorePend(pte_osSemaphoreHandle handle, unsigned int *pTimeoutMsecs)
{
   unsigned int timeoutUsecs;
   unsigned int *pTimeoutUsecs;
   SceUInt result;
   pte_osResult osResult;

   if (pTimeoutMsecs == NULL)
      pTimeoutUsecs = NULL;
   else
   {
      timeoutUsecs = *pTimeoutMsecs * 1000;
      pTimeoutUsecs = &timeoutUsecs;
   }

   result = sceKernelWaitSema(handle, 1, pTimeoutUsecs);

   if (result == SCE_KERNEL_ERROR_OK)
      return PTE_OS_OK;

   if (result == SCE_KERNEL_ERROR_WAIT_TIMEOUT)
      return PTE_OS_TIMEOUT;

   return PTE_OS_GENERAL_FAILURE;
}