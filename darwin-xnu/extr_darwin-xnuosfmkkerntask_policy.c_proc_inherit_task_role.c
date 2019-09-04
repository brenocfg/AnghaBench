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
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_ROLE ; 
 int proc_get_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_set_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
proc_inherit_task_role(task_t new_task,
                       task_t old_task)
{
	int role;

	/* inherit the role from old task to new task */
	role = proc_get_task_policy(old_task, TASK_POLICY_ATTRIBUTE, TASK_POLICY_ROLE);
	proc_set_task_policy(new_task, TASK_POLICY_ATTRIBUTE, TASK_POLICY_ROLE, role);
}