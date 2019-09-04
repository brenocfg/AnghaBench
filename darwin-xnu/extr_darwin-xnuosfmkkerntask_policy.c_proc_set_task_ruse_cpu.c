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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* task_t ;
struct TYPE_7__ {int policy_ru_cpu_ext; int policy_ru_cpu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_NONE 133 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_NOTIFY_EXC 132 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_NOTIFY_KQ 131 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_SUSPEND 130 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_TERMINATE 129 
#define  TASK_POLICY_RESOURCE_ATTRIBUTE_THROTTLE 128 
 int TASK_RUSECPU_FLAGS_DEADLINE ; 
 int TASK_RUSECPU_FLAGS_PERTHR_LIMIT ; 
 int TASK_RUSECPU_FLAGS_PROC_LIMIT ; 
 TYPE_1__* current_task () ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int task_set_cpuusage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

int 
proc_set_task_ruse_cpu(task_t task, uint32_t policy, uint8_t percentage, uint64_t interval, uint64_t deadline,
	int cpumon_entitled)
{
	int error = 0;
	int scope;

 	/*
 	 * Enforce the matrix of supported configurations for policy, percentage, and deadline.
 	 */
 	switch (policy) {
 	// If no policy is explicitly given, the default is to throttle.
 	case TASK_POLICY_RESOURCE_ATTRIBUTE_NONE:
	case TASK_POLICY_RESOURCE_ATTRIBUTE_THROTTLE:
		if (deadline != 0)
			return (ENOTSUP);
		scope = TASK_RUSECPU_FLAGS_PROC_LIMIT;
		break;
	case TASK_POLICY_RESOURCE_ATTRIBUTE_SUSPEND:
	case TASK_POLICY_RESOURCE_ATTRIBUTE_TERMINATE:
	case TASK_POLICY_RESOURCE_ATTRIBUTE_NOTIFY_KQ:
		if (percentage != 0)
			return (ENOTSUP);
		scope = TASK_RUSECPU_FLAGS_DEADLINE;
		break;
 	case TASK_POLICY_RESOURCE_ATTRIBUTE_NOTIFY_EXC:
		if (deadline != 0)
			return (ENOTSUP);
		scope = TASK_RUSECPU_FLAGS_PERTHR_LIMIT;
#ifdef CONFIG_NOMONITORS
		return (error);
#endif /* CONFIG_NOMONITORS */
		break;
	default:
		return (EINVAL);
	}

	task_lock(task);
	if (task != current_task()) {
		task->policy_ru_cpu_ext = policy;
	} else {
		task->policy_ru_cpu = policy;
	}
	error = task_set_cpuusage(task, percentage, interval, deadline, scope, cpumon_entitled);
	task_unlock(task);
	return(error);
}