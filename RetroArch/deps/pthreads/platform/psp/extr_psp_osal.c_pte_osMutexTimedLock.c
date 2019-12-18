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
typedef  int /*<<< orphan*/  pte_osResult ;
typedef  int /*<<< orphan*/  pte_osMutexHandle ;
typedef  unsigned int SceUInt ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_OS_OK ; 
 int /*<<< orphan*/  PTE_OS_TIMEOUT ; 
 int sceKernelWaitSema (int /*<<< orphan*/ ,int,unsigned int*) ; 

pte_osResult pte_osMutexTimedLock(pte_osMutexHandle handle, unsigned int timeoutMsecs)
{
   SceUInt timeoutUsecs = timeoutMsecs*1000;
   int status = sceKernelWaitSema(handle, 1, &timeoutUsecs);

   /* Assume that any error from sceKernelWaitSema was due to a timeout */
   if (status < 0)
      return PTE_OS_TIMEOUT;

   return PTE_OS_OK;
}