#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_7__ {int applied_ru_cpu; int applied_ru_cpu_ext; void* bsd_info; void* policy_ru_cpu; void* policy_ru_cpu_ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_CPU_RESOURCE_USAGE ; 
 void* TASK_POLICY_RESOURCE_ATTRIBUTE_DEFAULT ; 
 int TASK_POLICY_RESOURCE_ATTRIBUTE_NONE ; 
 TYPE_1__* current_task () ; 
 int /*<<< orphan*/  proc_restore_resource_actions (void*,int /*<<< orphan*/ ,int) ; 
 int task_clear_cpuusage_locked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

int 
proc_clear_task_ruse_cpu(task_t task, int cpumon_entitled)
{
	int error = 0;
	int action;
	void * bsdinfo = NULL;

	task_lock(task);
	if (task != current_task()) {
		task->policy_ru_cpu_ext = TASK_POLICY_RESOURCE_ATTRIBUTE_DEFAULT;
	} else {
		task->policy_ru_cpu = TASK_POLICY_RESOURCE_ATTRIBUTE_DEFAULT;
	}

	error = task_clear_cpuusage_locked(task, cpumon_entitled);
	if (error != 0)
		goto out;	

	action = task->applied_ru_cpu;
	if (task->applied_ru_cpu_ext != TASK_POLICY_RESOURCE_ATTRIBUTE_NONE) {
		/* reset action */
		task->applied_ru_cpu_ext = TASK_POLICY_RESOURCE_ATTRIBUTE_NONE;
	}
	if (action != TASK_POLICY_RESOURCE_ATTRIBUTE_NONE) {
		bsdinfo = task->bsd_info;
		task_unlock(task);
		proc_restore_resource_actions(bsdinfo, TASK_POLICY_CPU_RESOURCE_USAGE, action);
		goto out1;
	}

out:
	task_unlock(task);
out1:
	return(error);

}