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
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  _kernelrpc_mach_port_special_reply_port_reset_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mach_port_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 

kern_return_t
mach_sync_ipc_link_monitoring_stop(mach_port_t srp, boolean_t* in_effect)
{
	kern_return_t kr;
	boolean_t link_broken = TRUE;

	kr = _kernelrpc_mach_port_special_reply_port_reset_link(mach_task_self(), srp, &link_broken);

	/*
	 * We return if the sync IPC priority inversion avoidance facility took
	 * effect, so if the link was broken it didn't take effect.
	 * Flip the return.
	 */
	*in_effect = !link_broken;

	mach_port_deallocate(mach_task_self(), srp);

	return kr;
}