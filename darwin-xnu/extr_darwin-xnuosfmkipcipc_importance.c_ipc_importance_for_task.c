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
typedef  scalar_t__ boolean_t ;
struct TYPE_12__ {int iit_made; int iit_bits; int /*<<< orphan*/  iit_inherits; int /*<<< orphan*/  iit_kmsgs; scalar_t__ iit_legacy_externdrop; scalar_t__ iit_legacy_externcnt; scalar_t__ iit_externdrop; scalar_t__ iit_externcnt; scalar_t__ iit_assertcnt; scalar_t__ iit_transitions; scalar_t__ iit_updatetime; scalar_t__ iit_filelocks; scalar_t__ iit_reserved; scalar_t__ iit_updatepolicy; scalar_t__ iit_live_donor; scalar_t__ iit_donor; scalar_t__ iit_denap; scalar_t__ iit_receiver; int /*<<< orphan*/ * iit_updateq; TYPE_1__* iit_task; } ;
struct TYPE_11__ {TYPE_2__* task_imp_base; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int IIE_TYPE_TASK ; 
 TYPE_2__* IIT_NULL ; 
 scalar_t__ IIT_REFS (TYPE_2__*) ; 
 scalar_t__ IIT_REFS_MAX ; 
 TYPE_1__* TASK_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_task_reference_internal (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_task_zone ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_reference (TYPE_1__*) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

ipc_importance_task_t
ipc_importance_for_task(task_t task, boolean_t made)
{
	ipc_importance_task_t task_elem;
	boolean_t first_pass = TRUE;

	assert(TASK_NULL != task);

 retry:
	/* No use returning anything for inactive task */
	if (!task->active)
		return IIT_NULL;

	ipc_importance_lock();
	task_elem = task->task_imp_base;
	if (IIT_NULL != task_elem) {
		/* Add a made reference (borrowing active task ref to do it) */
		if (made) {
			if (0 == task_elem->iit_made++) {
				assert(IIT_REFS_MAX > IIT_REFS(task_elem));
				ipc_importance_task_reference_internal(task_elem);
			}
		} else {
			assert(IIT_REFS_MAX > IIT_REFS(task_elem));
			ipc_importance_task_reference_internal(task_elem);
		}
		ipc_importance_unlock();
		return task_elem;
	}
	ipc_importance_unlock();

	if (!first_pass)
		return IIT_NULL;
	first_pass = FALSE;

	/* Need to make one - may race with others (be prepared to drop) */
	task_elem = (ipc_importance_task_t)zalloc(ipc_importance_task_zone);
	if (IIT_NULL == task_elem)
		goto retry;

	task_elem->iit_bits = IIE_TYPE_TASK | 2; /* one for task, one for return/made */
	task_elem->iit_made = (made) ? 1 : 0;
	task_elem->iit_task = task; /* take actual ref when we're sure */
	task_elem->iit_updateq = NULL;
	task_elem->iit_receiver = 0;
	task_elem->iit_denap = 0;
	task_elem->iit_donor = 0;
	task_elem->iit_live_donor = 0;
	task_elem->iit_updatepolicy = 0;
	task_elem->iit_reserved = 0;
	task_elem->iit_filelocks = 0;
	task_elem->iit_updatetime = 0;
	task_elem->iit_transitions = 0;
	task_elem->iit_assertcnt = 0;
	task_elem->iit_externcnt = 0;
	task_elem->iit_externdrop = 0;
	task_elem->iit_legacy_externcnt = 0;
	task_elem->iit_legacy_externdrop = 0;
#if IIE_REF_DEBUG
	ipc_importance_counter_init(&task_elem->iit_elem);
#endif
	queue_init(&task_elem->iit_kmsgs);
	queue_init(&task_elem->iit_inherits);

	ipc_importance_lock();
	if (!task->active) {
		ipc_importance_unlock();
		zfree(ipc_importance_task_zone, task_elem);
		return IIT_NULL;
	}

	/* did we lose the race? */
	if (IIT_NULL != task->task_imp_base) {
		ipc_importance_unlock();
		zfree(ipc_importance_task_zone, task_elem);
		goto retry;
	}

	/* we won the race */
	task->task_imp_base = task_elem;
	task_reference(task);
#if DEVELOPMENT || DEBUG
	queue_enter(&global_iit_alloc_queue, task_elem, ipc_importance_task_t, iit_allocation);
	task_importance_update_owner_info(task);
#endif
	ipc_importance_unlock();

	return task_elem;
}