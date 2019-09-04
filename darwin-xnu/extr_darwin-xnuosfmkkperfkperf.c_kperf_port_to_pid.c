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
typedef  scalar_t__ task_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ TASK_NULL ; 
 scalar_t__ port_name_to_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_deallocate_internal (scalar_t__) ; 
 int task_pid (scalar_t__) ; 

int
kperf_port_to_pid(mach_port_name_t portname)
{
	if (!MACH_PORT_VALID(portname)) {
		return -1;
	}

	task_t task = port_name_to_task(portname);
	if (task == TASK_NULL) {
		return -1;
	}
	pid_t pid = task_pid(task);
	/* drop the ref taken by port_name_to_task */
	task_deallocate_internal(task);

	return pid;
}