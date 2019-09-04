#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_2__* ipc_importance_task_t ;
struct TYPE_10__ {int iit_assertcnt; int /*<<< orphan*/  iit_legacy_externcnt; int /*<<< orphan*/  iit_externcnt; TYPE_1__* iit_task; } ;
struct TYPE_9__ {int /*<<< orphan*/  bsd_info; } ;

/* Variables and functions */
 scalar_t__ IIT_EXTERN (TYPE_2__*) ; 
 scalar_t__ IIT_LEGACY_EXTERN (TYPE_2__*) ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_1__* TASK_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int ipc_importance_task_is_any_receiver_type (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 char* proc_name_address (int /*<<< orphan*/ ) ; 
 int task_pid (TYPE_1__*) ; 

kern_return_t
ipc_importance_task_hold_legacy_external_assertion(ipc_importance_task_t task_imp, uint32_t count)
{
	task_t target_task;
	uint32_t target_assertcnt;
	uint32_t target_externcnt;
	uint32_t target_legacycnt;

	kern_return_t ret;

	ipc_importance_lock();
	target_task = task_imp->iit_task;

#if IMPORTANCE_TRACE
	int target_pid = task_pid(target_task);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_ASSERTION, (IMP_HOLD | TASK_POLICY_EXTERNAL))) | DBG_FUNC_START,
		proc_selfpid(), target_pid, task_imp->iit_assertcnt, IIT_LEGACY_EXTERN(task_imp), 0);
#endif

	if (IIT_LEGACY_EXTERN(task_imp) == 0) {
		/* Only allowed to take a new boost assertion when holding an external boost */
		/* save data for diagnostic printf below */
		target_assertcnt = task_imp->iit_assertcnt;
		target_externcnt = IIT_EXTERN(task_imp);
		target_legacycnt = IIT_LEGACY_EXTERN(task_imp);
		ret = KERN_FAILURE;
		count = 0;
	} else {
		assert(ipc_importance_task_is_any_receiver_type(task_imp));
		assert(0 < task_imp->iit_assertcnt);
		assert(0 < IIT_EXTERN(task_imp));
		task_imp->iit_assertcnt += count;
		task_imp->iit_externcnt += count;
		task_imp->iit_legacy_externcnt += count;
		ret = KERN_SUCCESS;
	}
	ipc_importance_unlock();

#if IMPORTANCE_TRACE
	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_ASSERTION, (IMP_HOLD | TASK_POLICY_EXTERNAL))) | DBG_FUNC_END,
				  proc_selfpid(), target_pid, task_imp->iit_assertcnt, IIT_LEGACY_EXTERN(task_imp), 0);
        // This covers the legacy case where a task takes an extra boost.
	DTRACE_BOOST5(receive_boost, task_t, target_task, int, target_pid, int, proc_selfpid(), int, count, int, task_imp->iit_assertcnt);
#endif

	if (KERN_FAILURE == ret && target_task != TASK_NULL) {
		printf("BUG in process %s[%d]: "
		       "attempt to acquire an additional legacy external boost assertion without holding an existing legacy external assertion. "
		       "(%d total, %d external, %d legacy-external)\n",
		       proc_name_address(target_task->bsd_info), task_pid(target_task),
		       target_assertcnt, target_externcnt, target_legacycnt);
	}

	return(ret);
}