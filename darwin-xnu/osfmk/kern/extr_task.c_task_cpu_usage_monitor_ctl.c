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
typedef  int uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  rusage_cpu_flags; } ;

/* Variables and functions */
 int CPUMON_MAKE_FATAL ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  TASK_RUSECPU_FLAGS_FATAL_CPUMON ; 

kern_return_t
task_cpu_usage_monitor_ctl(task_t task, uint32_t *flags)
{
	int error = KERN_SUCCESS;

	if (*flags & CPUMON_MAKE_FATAL) {
		task->rusage_cpu_flags |= TASK_RUSECPU_FLAGS_FATAL_CPUMON;
	} else {
		error = KERN_INVALID_ARGUMENT;
	}

	return error;
}