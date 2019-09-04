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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ipc_importance_task_t ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int ipc_importance_task_hold_internal_assertion_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipc_importance_task_is_any_receiver_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 

int
ipc_importance_task_hold_internal_assertion(ipc_importance_task_t task_imp, uint32_t count)
{
	int ret = KERN_SUCCESS;

	if (ipc_importance_task_is_any_receiver_type(task_imp)) {
		ipc_importance_lock();
		ret = ipc_importance_task_hold_internal_assertion_locked(task_imp, count);
		ipc_importance_unlock();
	}
	return ret;
}