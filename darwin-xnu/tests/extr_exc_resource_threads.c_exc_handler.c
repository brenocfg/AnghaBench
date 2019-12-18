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
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  exception_behavior_t ;

/* Variables and functions */
 int EXCEPTION_DEFAULT ; 
 int EXC_MASK_CORPSE_NOTIFY ; 
 int EXC_MASK_CRASH ; 
 scalar_t__ KERN_SUCCESS ; 
 int MACH_EXCEPTION_CODES ; 
 int /*<<< orphan*/  MACH_MSG_SIZE_RELIABLE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  T_FAIL (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_error_string (scalar_t__) ; 
 int /*<<< orphan*/  mach_exc_server ; 
 scalar_t__ mach_msg_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mach_port_insert_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  sync_sema ; 
 scalar_t__ task_set_exception_ports (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
exc_handler(void * arg)
{
#pragma unused(arg)
	kern_return_t kret;
	mach_port_t exception_port;

	kret = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &exception_port);
	if (kret != KERN_SUCCESS)
		T_FAIL("mach_port_allocate: %s (%d)", mach_error_string(kret), kret);

	kret = mach_port_insert_right(mach_task_self(), exception_port, exception_port, MACH_MSG_TYPE_MAKE_SEND);
	if (kret != KERN_SUCCESS)
		T_FAIL("mach_port_insert_right: %s (%d)", mach_error_string(kret), kret);

	kret = task_set_exception_ports(mach_task_self(), EXC_MASK_CRASH | EXC_MASK_CORPSE_NOTIFY, exception_port,
	                                (exception_behavior_t)(EXCEPTION_DEFAULT | MACH_EXCEPTION_CODES), 0);
	if (kret != KERN_SUCCESS)
		T_FAIL("task_set_exception_ports: %s (%d)", mach_error_string(kret), kret);

	dispatch_semaphore_signal(sync_sema);

	kret = mach_msg_server(mach_exc_server, MACH_MSG_SIZE_RELIABLE, exception_port, 0);
	if (kret != KERN_SUCCESS)
		T_FAIL("mach_msg_server: %s (%d)", mach_error_string(kret), kret);

	return NULL;
}