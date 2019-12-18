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
struct TYPE_3__ {int size; int currentPriority; } ;
typedef  TYPE_1__ SceKernelThreadInfo ;

/* Variables and functions */
 int /*<<< orphan*/  sceKernelReferThreadStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 

int pte_osThreadGetPriority(pte_osThreadHandle threadHandle)
{
   SceKernelThreadInfo thinfo;

   thinfo.size = sizeof(SceKernelThreadInfo);

   sceKernelReferThreadStatus(threadHandle, &thinfo);

   return thinfo.currentPriority;
}