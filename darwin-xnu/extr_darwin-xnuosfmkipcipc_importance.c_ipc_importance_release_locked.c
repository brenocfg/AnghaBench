#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* ipc_importance_task_t ;
typedef  TYPE_1__* ipc_importance_inherit_t ;
typedef  int /*<<< orphan*/  ipc_importance_elem_t ;
struct TYPE_11__ {int /*<<< orphan*/  iii_externdrop; int /*<<< orphan*/  iii_externcnt; int /*<<< orphan*/  iii_donating; int /*<<< orphan*/  iit_externdrop; int /*<<< orphan*/  iit_externcnt; struct TYPE_11__* iii_to_task; int /*<<< orphan*/  iit_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IIE_NULL ; 
 scalar_t__ IIE_REFS (int /*<<< orphan*/ ) ; 
 int IIE_TYPE (int /*<<< orphan*/ ) ; 
#define  IIE_TYPE_INHERIT 129 
#define  IIE_TYPE_TASK 128 
 int /*<<< orphan*/  III_EXTERN (TYPE_1__*) ; 
 TYPE_1__* IIT_NULL ; 
 int /*<<< orphan*/  IIT_UPDATE_DROP ; 
 int /*<<< orphan*/  TASK_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_inherit_unlink (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_inherit_zone ; 
 scalar_t__ ipc_importance_release_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_check_transition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipc_importance_task_is_any_receiver_type (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_task_propagate_assertion_locked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ipc_importance_task_zone ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
ipc_importance_release_locked(ipc_importance_elem_t elem)
{
	assert(0 < IIE_REFS(elem));

#if IMPORTANCE_DEBUG
	ipc_importance_inherit_t temp_inherit;
	ipc_importance_task_t link_task;
	ipc_kmsg_t temp_kmsg;
	uint32_t expected = 0;

	if (0 < elem->iie_made)
		expected++;

	link_task = (IIE_TYPE_INHERIT == IIE_TYPE(elem)) ?
		((ipc_importance_inherit_t)elem)->iii_to_task : 
		(ipc_importance_task_t)elem;

	queue_iterate(&link_task->iit_kmsgs, temp_kmsg, ipc_kmsg_t, ikm_inheritance)
		if (temp_kmsg->ikm_importance == elem)
			expected++;
	queue_iterate(&link_task->iit_inherits, temp_inherit,
		      ipc_importance_inherit_t, iii_inheritance)
		if (temp_inherit->iii_from_elem == elem)
			expected++;
	if (IIE_REFS(elem) < expected + 1)
		panic("ipc_importance_release_locked (%p)", elem);
#endif /* IMPORTANCE_DEBUG */

	if (0 < ipc_importance_release_internal(elem)) {
		ipc_importance_unlock();
		return;
	}

	/* last ref */

	switch (IIE_TYPE(elem)) {

	/* just a "from" task reference to drop */
	case IIE_TYPE_TASK:
	{
		ipc_importance_task_t task_elem;

		task_elem = (ipc_importance_task_t)elem;

		/* the task can't still hold a reference on the task importance */
		assert(TASK_NULL == task_elem->iit_task);

#if DEVELOPMENT || DEBUG
		queue_remove(&global_iit_alloc_queue, task_elem, ipc_importance_task_t, iit_allocation);
#endif

		ipc_importance_unlock();

		zfree(ipc_importance_task_zone, task_elem);
		break;
	}

	/* dropping an inherit element */
	case IIE_TYPE_INHERIT:
	{
		ipc_importance_inherit_t inherit = (ipc_importance_inherit_t)elem;
		ipc_importance_task_t to_task = inherit->iii_to_task;
		ipc_importance_elem_t from_elem;

		assert(IIT_NULL != to_task);
		assert(ipc_importance_task_is_any_receiver_type(to_task));

		/* unlink the inherit from its source element */
		from_elem = ipc_importance_inherit_unlink(inherit);
		assert(IIE_NULL != from_elem);

		/*
		 * The attribute might have pending external boosts if the attribute
		 * was given out during exec, drop them from the appropriate destination
		 * task.
		 *
		 * The attribute will not have any pending external boosts if the
		 * attribute was given out to voucher system since it would have been
		 * dropped by ipc_importance_release_value, but there is not way to
		 * detect that, thus if the attribute has a pending external boost,
		 * drop them from the appropriate destination task.
		 *
		 * The inherit attribute from exec and voucher system would not
		 * get deduped to each other, thus dropping the external boost
		 * from destination task at two different places will not have
		 * any unintended side effects.
		 */
		assert(inherit->iii_externcnt >= inherit->iii_externdrop);
		if (inherit->iii_donating) {
			uint32_t assertcnt = III_EXTERN(inherit);

			assert(ipc_importance_task_is_any_receiver_type(to_task));
			assert(to_task->iit_externcnt >= inherit->iii_externcnt);
			assert(to_task->iit_externdrop >= inherit->iii_externdrop);
			to_task->iit_externcnt -= inherit->iii_externcnt;
			to_task->iit_externdrop -= inherit->iii_externdrop;
			inherit->iii_externcnt = 0;
			inherit->iii_externdrop = 0;
			inherit->iii_donating = FALSE;

			/* adjust the internal assertions - and propagate as needed */
			if (ipc_importance_task_check_transition(to_task, IIT_UPDATE_DROP, assertcnt)) {
				ipc_importance_task_propagate_assertion_locked(to_task, IIT_UPDATE_DROP, TRUE);
			}
		} else {
			inherit->iii_externcnt = 0;
			inherit->iii_externdrop = 0;
		}

		/* release the reference on the source element */
		ipc_importance_release_locked(from_elem);
		/* unlocked on return */

		/* release the reference on the destination task */
		ipc_importance_task_release(to_task);

		/* free the inherit */
		zfree(ipc_importance_inherit_zone, inherit);
		break;
	}
	}
}