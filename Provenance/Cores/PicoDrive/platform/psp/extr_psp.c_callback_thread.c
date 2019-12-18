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
typedef  int /*<<< orphan*/  SceSize ;

/* Variables and functions */
 int /*<<< orphan*/  exit_callback ; 
 int /*<<< orphan*/  lprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_callback ; 
 int sceKernelCreateCallback (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sceKernelGetThreadCurrentPriority () ; 
 int /*<<< orphan*/  sceKernelGetThreadId () ; 
 int /*<<< orphan*/  sceKernelRegisterExitCallback (int) ; 
 int /*<<< orphan*/  sceKernelSleepThreadCB () ; 
 int /*<<< orphan*/  scePowerRegisterCallback (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int callback_thread(SceSize args, void *argp)
{
	int cbid;

	lprintf("callback_thread started with id %08x, priority %i\n",
		sceKernelGetThreadId(), sceKernelGetThreadCurrentPriority());

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	cbid = sceKernelCreateCallback("Power Callback", power_callback, NULL);
	scePowerRegisterCallback(0, cbid);

	sceKernelSleepThreadCB();

	return 0;
}