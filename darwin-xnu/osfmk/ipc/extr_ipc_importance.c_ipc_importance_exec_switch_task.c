#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* ipc_importance_task_t ;
typedef  int /*<<< orphan*/  ipc_importance_inherit_t ;
struct TYPE_11__ {TYPE_1__* iit_task; } ;
struct TYPE_10__ {TYPE_2__* task_imp_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  III_NULL ; 
 TYPE_2__* IIT_NULL ; 
 int /*<<< orphan*/  ipc_importance_inherit_from_task (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  task_importance_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  task_importance_update_owner_info (TYPE_1__*) ; 

ipc_importance_inherit_t
ipc_importance_exec_switch_task(
	task_t old_task,
	task_t new_task)
{
	ipc_importance_inherit_t inherit = III_NULL;
	ipc_importance_task_t old_task_imp = IIT_NULL;
	ipc_importance_task_t new_task_imp = IIT_NULL;

	task_importance_reset(old_task);

	/* Create an importance linkage from old_task to new_task */
	inherit = ipc_importance_inherit_from_task(old_task, new_task);

	/* Switch task importance base from old task to new task */
	ipc_importance_lock();

	old_task_imp = old_task->task_imp_base;
	new_task_imp = new_task->task_imp_base;

	old_task_imp->iit_task = new_task;
	new_task_imp->iit_task = old_task;

	old_task->task_imp_base = new_task_imp;
	new_task->task_imp_base = old_task_imp;

#if DEVELOPMENT || DEBUG
	/*
	 * Update the pid an proc name for importance base if any
	 */
	task_importance_update_owner_info(new_task);
#endif
	ipc_importance_unlock();

	return inherit;
}