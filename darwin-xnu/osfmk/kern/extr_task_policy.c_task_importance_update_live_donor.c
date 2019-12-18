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
typedef  scalar_t__ ipc_importance_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IIT_NULL ; 
 scalar_t__ ipc_importance_for_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_release (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_update_live_donor (scalar_t__) ; 

__attribute__((used)) static void
task_importance_update_live_donor(task_t target_task)
{
#if IMPORTANCE_INHERITANCE

	ipc_importance_task_t task_imp;

	task_imp = ipc_importance_for_task(target_task, FALSE);
	if (IIT_NULL != task_imp) {
		ipc_importance_task_update_live_donor(task_imp);
		ipc_importance_task_release(task_imp);
	}
#endif /* IMPORTANCE_INHERITANCE */
}