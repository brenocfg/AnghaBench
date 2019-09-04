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
typedef  scalar_t__ ipc_importance_task_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ IIT_NULL ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_reset_locked (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 

void
ipc_importance_reset(ipc_importance_task_t task_imp, boolean_t donor)
{
	if (IIT_NULL == task_imp) {
		return;
	}
	ipc_importance_lock();
	ipc_importance_reset_locked(task_imp, donor);
	ipc_importance_unlock();
}