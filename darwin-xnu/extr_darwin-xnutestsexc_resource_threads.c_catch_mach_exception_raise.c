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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  exception_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_CORPSE_NOTIFY ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dispatch_semaphore_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_for_task (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_sema ; 

kern_return_t
catch_mach_exception_raise(mach_port_t exception_port,
                           mach_port_t thread,
                           mach_port_t task,
                           exception_type_t exception,
                           mach_exception_data_t code,
                           mach_msg_type_number_t code_count)
{
#pragma unused(exception_port, thread, task, code, code_count)
	pid_t pid;
	pid_for_task(task, &pid);
	T_ASSERT_EQ(exception, EXC_CORPSE_NOTIFY, "exception type");
	T_ASSERT_POSIX_ZERO(kill(pid, SIGKILL), "kill");
	dispatch_semaphore_signal(sync_sema);
	return KERN_SUCCESS;
}