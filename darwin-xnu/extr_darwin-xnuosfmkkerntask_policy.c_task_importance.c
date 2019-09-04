#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
struct task_pend_token {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  integer_t ;
struct TYPE_10__ {int /*<<< orphan*/  importance; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 scalar_t__ TASK_CONTROL_APPLICATION ; 
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  TASK_POLICY_ROLE ; 
 TYPE_1__* kernel_task ; 
 scalar_t__ proc_get_effective_task_policy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_policy_update_complete_unlocked (TYPE_1__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_policy_update_locked (TYPE_1__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

kern_return_t
task_importance(
	task_t				task,
	integer_t			importance)
{
	if (task == TASK_NULL || task == kernel_task)
		return (KERN_INVALID_ARGUMENT);

	task_lock(task);

	if (!task->active) {
		task_unlock(task);

		return (KERN_TERMINATED);
	}

	if (proc_get_effective_task_policy(task, TASK_POLICY_ROLE) >= TASK_CONTROL_APPLICATION) {
		task_unlock(task);

		return (KERN_INVALID_ARGUMENT);
	}

	task->importance = importance;

	struct task_pend_token pend_token = {};

	task_policy_update_locked(task, &pend_token);

	task_unlock(task);

	task_policy_update_complete_unlocked(task, &pend_token);

	return (KERN_SUCCESS);
}