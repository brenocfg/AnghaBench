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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* ipc_importance_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  iit_filelocks; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 scalar_t__ ipc_importance_task_hold_internal_assertion_locked (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ipc_importance_task_is_any_receiver_type (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 

kern_return_t
ipc_importance_task_hold_file_lock_assertion(ipc_importance_task_t task_imp, uint32_t count)
{
	kern_return_t ret = KERN_SUCCESS;

	if (ipc_importance_task_is_any_receiver_type(task_imp)) {
		ipc_importance_lock();
		ret = ipc_importance_task_hold_internal_assertion_locked(task_imp, count);
		if (KERN_SUCCESS == ret) {
			task_imp->iit_filelocks += count;
		}
		ipc_importance_unlock();
	}
	return ret;
}