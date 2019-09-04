#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_task_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int iit_donor; int /*<<< orphan*/  iit_task; int /*<<< orphan*/  iit_transitions; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMP_DONOR_CHANGE ; 
 int /*<<< orphan*/  IMP_DONOR_INIT_DONOR_STATE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

void
ipc_importance_task_mark_donor(ipc_importance_task_t task_imp, boolean_t donating)
{
	assert(task_imp != NULL);

	ipc_importance_lock();

	int old_donor = task_imp->iit_donor;

	task_imp->iit_donor = (donating ? 1 : 0);

	if (task_imp->iit_donor > 0 && old_donor == 0)
		task_imp->iit_transitions++;

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
	                          (IMPORTANCE_CODE(IMP_DONOR_CHANGE, IMP_DONOR_INIT_DONOR_STATE)) | DBG_FUNC_NONE,
	                          task_pid(task_imp->iit_task), donating,
	                          old_donor, task_imp->iit_donor, 0);
	
	ipc_importance_unlock();
}