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
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_VOUCHER_ATTR_KEY_PTHPRIORITY ; 
 int /*<<< orphan*/  ipc_pthread_priority_manager ; 
 int /*<<< orphan*/  ipc_pthread_priority_voucher_attr_control ; 
 scalar_t__ ipc_register_well_known_mach_voucher_attr_manager (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
ipc_pthread_priority_init()
{
	kern_return_t kr = KERN_SUCCESS;

	/* Register the ipc_pthread_priority manager with the Vouchers sub system. */
	kr = ipc_register_well_known_mach_voucher_attr_manager(
	                &ipc_pthread_priority_manager,
	                0,
	                MACH_VOUCHER_ATTR_KEY_PTHPRIORITY,
	                &ipc_pthread_priority_voucher_attr_control);
	if (kr != KERN_SUCCESS )
		panic("IPC_PTHREAD_PRIORITY subsystem initialization failed");

	kprintf("IPC_PTHREAD_PRIORITY subsystem is initialized\n");
	return ;
}