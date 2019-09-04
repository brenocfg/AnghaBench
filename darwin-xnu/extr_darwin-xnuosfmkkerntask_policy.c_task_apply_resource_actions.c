#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct TYPE_5__ {int applied_ru_cpu_ext; int policy_ru_cpu_ext; void* bsd_info; } ;

/* Variables and functions */
#define  TASK_POLICY_CPU_RESOURCE_USAGE 133 
#define  TASK_POLICY_DISK_RESOURCE_USAGE 132 
#define  TASK_POLICY_NETWORK_RESOURCE_USAGE 131 
#define  TASK_POLICY_POWER_RESOURCE_USAGE 130 
 int TASK_POLICY_RESOURCE_ATTRIBUTE_NONE ; 
#define  TASK_POLICY_VIRTUALMEM_RESOURCE_USAGE 129 
#define  TASK_POLICY_WIREDMEM_RESOURCE_USAGE 128 
 int /*<<< orphan*/  proc_apply_resource_actions (void*,int const,int) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

__attribute__((used)) static int
task_apply_resource_actions(task_t task, int type)
{
	int action = TASK_POLICY_RESOURCE_ATTRIBUTE_NONE;
	void * bsdinfo = NULL;
	
	switch (type) {
		case TASK_POLICY_CPU_RESOURCE_USAGE:
			break;
		case TASK_POLICY_WIREDMEM_RESOURCE_USAGE:
		case TASK_POLICY_VIRTUALMEM_RESOURCE_USAGE:
		case TASK_POLICY_DISK_RESOURCE_USAGE:
		case TASK_POLICY_NETWORK_RESOURCE_USAGE:
		case TASK_POLICY_POWER_RESOURCE_USAGE:
			return(0);

		default:
			return(1);
	};

	/* only cpu actions for now */
	task_lock(task);
	
	if (task->applied_ru_cpu_ext == TASK_POLICY_RESOURCE_ATTRIBUTE_NONE) {
		/* apply action */
		task->applied_ru_cpu_ext = task->policy_ru_cpu_ext;
		action = task->applied_ru_cpu_ext;
	} else {
		action = task->applied_ru_cpu_ext;
	}

	if (action != TASK_POLICY_RESOURCE_ATTRIBUTE_NONE) {
		bsdinfo = task->bsd_info;
		task_unlock(task);
		proc_apply_resource_actions(bsdinfo, TASK_POLICY_CPU_RESOURCE_USAGE, action);
	} else
		task_unlock(task);

	return(0);
}