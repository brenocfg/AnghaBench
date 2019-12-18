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
typedef  int uint32_t ;
typedef  TYPE_1__* task_t ;
typedef  int kern_return_t ;
typedef  TYPE_2__* ipc_importance_task_t ;
struct TYPE_12__ {int iit_assertcnt; scalar_t__ iit_legacy_externdrop; scalar_t__ iit_legacy_externcnt; scalar_t__ iit_externdrop; scalar_t__ iit_externcnt; TYPE_1__* iit_task; } ;
struct TYPE_11__ {int /*<<< orphan*/  bsd_info; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int IIT_EXTERN (TYPE_2__*) ; 
 int IIT_LEGACY_EXTERN (TYPE_2__*) ; 
 int /*<<< orphan*/  IIT_UPDATE_DROP ; 
 int IMPORTANCE_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMP_ASSERTION ; 
 int IMP_DROP ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int KERN_FAILURE ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 TYPE_1__* TASK_NULL ; 
 int TASK_POLICY_EXTERNAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 scalar_t__ ipc_importance_task_check_transition (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int ipc_importance_task_is_any_receiver_type (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_task_propagate_assertion_locked (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 char* proc_name_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_selfpid () ; 
 int task_pid (TYPE_1__*) ; 

kern_return_t
ipc_importance_task_drop_legacy_external_assertion(ipc_importance_task_t task_imp, uint32_t count)
{
	int ret = KERN_SUCCESS;
	task_t target_task;
	uint32_t target_assertcnt;
	uint32_t target_externcnt;
	uint32_t target_legacycnt;

	if (count > 1) {
		return KERN_INVALID_ARGUMENT;
	}
		
	ipc_importance_lock();
	target_task = task_imp->iit_task;

#if IMPORTANCE_TRACE
	int target_pid = task_pid(target_task);

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_ASSERTION, (IMP_DROP | TASK_POLICY_EXTERNAL))) | DBG_FUNC_START,
		proc_selfpid(), target_pid, task_imp->iit_assertcnt, IIT_LEGACY_EXTERN(task_imp), 0);
#endif

	if (count > IIT_LEGACY_EXTERN(task_imp)) {
		/* Process over-released its boost count - save data for diagnostic printf */
		/* TODO: If count > 1, we should clear out as many external assertions as there are left. */
		target_assertcnt = task_imp->iit_assertcnt;
		target_externcnt = IIT_EXTERN(task_imp);
		target_legacycnt = IIT_LEGACY_EXTERN(task_imp);
		ret = KERN_FAILURE;
	} else {
		/* 
		 * decrement legacy external count from the top level and reflect
		 * into internal for this and all subsequent updates.
		 */
		assert(ipc_importance_task_is_any_receiver_type(task_imp));
		assert(IIT_EXTERN(task_imp) >= count);

		task_imp->iit_legacy_externdrop += count;
		task_imp->iit_externdrop += count;

		/* reset extern counters (if appropriate) */
		if (IIT_LEGACY_EXTERN(task_imp) == 0) {
			if (IIT_EXTERN(task_imp) != 0) {
				task_imp->iit_externcnt -= task_imp->iit_legacy_externcnt;
				task_imp->iit_externdrop -= task_imp->iit_legacy_externdrop;
			} else {
				task_imp->iit_externcnt = 0;
				task_imp->iit_externdrop = 0;
			}
			task_imp->iit_legacy_externcnt = 0;
			task_imp->iit_legacy_externdrop = 0;
		}
		
		/* reflect the drop to the internal assertion count (and effect any importance change) */
		if (ipc_importance_task_check_transition(task_imp, IIT_UPDATE_DROP, count)) {
			ipc_importance_task_propagate_assertion_locked(task_imp, IIT_UPDATE_DROP, TRUE);
		}
		ret = KERN_SUCCESS;
	}

#if IMPORTANCE_TRACE
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (IMPORTANCE_CODE(IMP_ASSERTION, (IMP_DROP | TASK_POLICY_EXTERNAL))) | DBG_FUNC_END,
					  proc_selfpid(), target_pid, task_imp->iit_assertcnt, IIT_LEGACY_EXTERN(task_imp), 0);
#endif

	ipc_importance_unlock();

	/* delayed printf for user-supplied data failures */
	if (KERN_FAILURE == ret && TASK_NULL != target_task) {
		printf("BUG in process %s[%d]: over-released legacy external boost assertions (%d total, %d external, %d legacy-external)\n",
		       proc_name_address(target_task->bsd_info), task_pid(target_task),
		       target_assertcnt, target_externcnt, target_legacycnt);
	}

	return(ret);
}