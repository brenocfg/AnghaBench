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
struct task_pend_token {int dummy; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int IMPORTANCE_CODE (int,int) ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int TASK_POLICY_TASK ; 
 int /*<<< orphan*/  proc_set_task_policy_locked (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_policy_update_complete_unlocked (int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_policy_update_locked (int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int tpending (struct task_pend_token*) ; 
 int /*<<< orphan*/  trequested_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trequested_1 (int /*<<< orphan*/ ) ; 

void
proc_set_task_policy2(task_t    task,
                      int       category,
                      int       flavor,
                      int       value,
                      int       value2)
{
	struct task_pend_token pend_token = {};

	task_lock(task);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(flavor, (category | TASK_POLICY_TASK))) | DBG_FUNC_START,
	                          task_pid(task), trequested_0(task),
	                          trequested_1(task), value, 0);

	proc_set_task_policy_locked(task, category, flavor, value, value2);

	task_policy_update_locked(task, &pend_token);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(flavor, (category | TASK_POLICY_TASK))) | DBG_FUNC_END,
	                          task_pid(task), trequested_0(task),
	                          trequested_1(task), tpending(&pend_token), 0);

	task_unlock(task);

	task_policy_update_complete_unlocked(task, &pend_token);
}