#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* task_t ;
typedef  TYPE_2__* ipc_importance_task_t ;
struct TYPE_12__ {TYPE_1__* iit_task; } ;
struct TYPE_11__ {TYPE_2__* task_imp_base; } ;

/* Variables and functions */
 TYPE_2__* IIT_NULL ; 
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_reset_locked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_release_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  task_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

void
ipc_importance_disconnect_task(task_t task)
{
	ipc_importance_task_t task_imp;

	task_lock(task);
	ipc_importance_lock();
	task_imp = task->task_imp_base;

	/* did somebody beat us to it? */
	if (IIT_NULL == task_imp) {
		ipc_importance_unlock();
		task_unlock(task);
		return;
	}

	/* disconnect the task from this importance */
	assert(task_imp->iit_task == task);
	task_imp->iit_task = TASK_NULL;
	task->task_imp_base = IIT_NULL;
	task_unlock(task);
	
	/* reset the effects the current task hold on the importance */
	ipc_importance_reset_locked(task_imp, TRUE);

	ipc_importance_task_release_locked(task_imp);
	/* importance unlocked */

	/* deallocate the task now that the importance is unlocked */
	task_deallocate(task);
}