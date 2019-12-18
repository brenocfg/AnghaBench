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

/* Variables and functions */
 scalar_t__ PGS_SuspendWake ; 
 scalar_t__ PGS_Suspending ; 
 int PSP_POWER_CB_POWER_SWITCH ; 
 int PSP_POWER_CB_RESUME_COMPLETE ; 
 int PSP_POWER_CB_STANDBY ; 
 int PSP_POWER_CB_SUSPENDING ; 
 scalar_t__ engineState ; 
 scalar_t__ engineStateSuspend ; 
 int /*<<< orphan*/  lprintf (char*,int) ; 
 int psp_unhandled_suspend ; 
 int /*<<< orphan*/  sceKernelDelayThread (int) ; 

__attribute__((used)) static int power_callback(int unknown, int pwrflags, void *common)
{
	lprintf("power_callback: flags: 0x%08X\n", pwrflags);

	/* check for power switch and suspending as one is manual and the other automatic */
	if (pwrflags & PSP_POWER_CB_POWER_SWITCH || pwrflags & PSP_POWER_CB_SUSPENDING || pwrflags & PSP_POWER_CB_STANDBY)
	{
		psp_unhandled_suspend = 1;
		if (engineState != PGS_Suspending)
			engineStateSuspend = engineState;
		sceKernelDelayThread(100000); // ??
	}
	else if (pwrflags & PSP_POWER_CB_RESUME_COMPLETE)
	{
		engineState = PGS_SuspendWake;
	}

	//sceDisplayWaitVblankStart();
	return 0;
}