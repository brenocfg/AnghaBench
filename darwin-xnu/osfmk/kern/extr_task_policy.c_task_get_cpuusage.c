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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_3__ {int rusage_cpu_flags; scalar_t__ rusage_cpu_deadline; scalar_t__ rusage_cpu_interval; scalar_t__ rusage_cpu_percentage; scalar_t__ rusage_cpu_perthr_interval; scalar_t__ rusage_cpu_perthr_percentage; } ;

/* Variables and functions */
 int TASK_RUSECPU_FLAGS_DEADLINE ; 
 int TASK_RUSECPU_FLAGS_PERTHR_LIMIT ; 
 int TASK_RUSECPU_FLAGS_PROC_LIMIT ; 

__attribute__((used)) static int
task_get_cpuusage(task_t task, uint8_t *percentagep, uint64_t *intervalp, uint64_t *deadlinep, int *scope)
{
	*percentagep = 0;
	*intervalp = 0;
	*deadlinep = 0;

	if ((task->rusage_cpu_flags & TASK_RUSECPU_FLAGS_PERTHR_LIMIT) != 0) {
		*scope = TASK_RUSECPU_FLAGS_PERTHR_LIMIT;
		*percentagep = task->rusage_cpu_perthr_percentage;
		*intervalp = task->rusage_cpu_perthr_interval;
	} else if ((task->rusage_cpu_flags & TASK_RUSECPU_FLAGS_PROC_LIMIT) != 0) {
		*scope = TASK_RUSECPU_FLAGS_PROC_LIMIT;
		*percentagep = task->rusage_cpu_percentage;
		*intervalp = task->rusage_cpu_interval;
	} else if ((task->rusage_cpu_flags & TASK_RUSECPU_FLAGS_DEADLINE) != 0) {
		*scope = TASK_RUSECPU_FLAGS_DEADLINE;
		*deadlinep = task->rusage_cpu_deadline;
	} else {
		*scope = 0;
	}

	return(0);
}