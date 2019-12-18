#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_3__* ipc_importance_task_t ;
typedef  TYPE_4__* ipc_importance_inherit_t ;
typedef  TYPE_5__* ipc_importance_elem_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_27__ {int /*<<< orphan*/  iie_task_refs_inherited; } ;
struct TYPE_32__ {TYPE_1__ iit_elem; } ;
struct TYPE_31__ {int /*<<< orphan*/  iie_kmsg_refs_dropped; int /*<<< orphan*/  iie_kmsg_refs_coalesced; int /*<<< orphan*/  iie_kmsg_refs_inherited; int /*<<< orphan*/  iie_kmsg_refs_added; } ;
struct TYPE_30__ {scalar_t__ iii_donating; int iii_externcnt; int iii_bits; int iii_depth; int /*<<< orphan*/  iii_elem; int /*<<< orphan*/  iii_kmsgs; TYPE_5__* iii_from_elem; TYPE_3__* iii_to_task; scalar_t__ iii_externdrop; scalar_t__ iii_made; } ;
struct TYPE_28__ {int /*<<< orphan*/  iie_task_refs_coalesced; int /*<<< orphan*/  iie_task_refs_added_inherit_from; } ;
struct TYPE_29__ {int iit_externcnt; TYPE_2__ iit_elem; int /*<<< orphan*/  iit_externdrop; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_5__* IIE_NULL ; 
 scalar_t__ IIE_REFS (TYPE_5__*) ; 
 int IIE_TYPE_INHERIT ; 
 scalar_t__ III_EXTERN (TYPE_4__*) ; 
 TYPE_4__* III_NULL ; 
 scalar_t__ III_REFS (TYPE_4__*) ; 
 scalar_t__ III_REFS_MAX ; 
 TYPE_3__* IIT_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  incr_ref_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_counter_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipc_importance_for_task (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* ipc_importance_inherit_find (TYPE_5__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ipc_importance_inherit_link (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ipc_importance_inherit_reference_internal (TYPE_4__*) ; 
 int /*<<< orphan*/  ipc_importance_inherit_zone ; 
 int /*<<< orphan*/  ipc_importance_lock () ; 
 int /*<<< orphan*/  ipc_importance_release_locked (TYPE_5__*) ; 
 int /*<<< orphan*/  ipc_importance_task_hold_internal_assertion_locked (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ipc_importance_task_is_any_receiver_type (TYPE_3__*) ; 
 scalar_t__ ipc_importance_task_is_donor (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_importance_task_release (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_importance_unlock () ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 TYPE_7__* task_imp ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static ipc_importance_inherit_t
ipc_importance_inherit_from_task(
	task_t from_task,
	task_t to_task)
{
	ipc_importance_task_t	to_task_imp = IIT_NULL;
	ipc_importance_task_t	from_task_imp = IIT_NULL;
	ipc_importance_elem_t 	from_elem = IIE_NULL;

	ipc_importance_inherit_t inherit = III_NULL;
	ipc_importance_inherit_t alloc = III_NULL;
	boolean_t donating;
	uint32_t depth = 1;

	to_task_imp = ipc_importance_for_task(to_task, FALSE);
	from_task_imp = ipc_importance_for_task(from_task, FALSE);
	from_elem = (ipc_importance_elem_t)from_task_imp;

	ipc_importance_lock();

	if (IIT_NULL == to_task_imp || IIT_NULL == from_task_imp) {
		goto out_locked;
	}

	/*
	 * No need to set up an inherit linkage if the to_task or from_task
	 * isn't a receiver of one type or the other.
	 */
	if (!ipc_importance_task_is_any_receiver_type(to_task_imp) ||
	    !ipc_importance_task_is_any_receiver_type(from_task_imp)) {
		goto out_locked;
	}

	/* Do not allow to create a linkage to self */
	if (to_task_imp == from_task_imp) {
		goto out_locked;
	}

	incr_ref_counter(to_task_imp->iit_elem.iie_task_refs_added_inherit_from);
	incr_ref_counter(from_elem->iie_kmsg_refs_added);

	/*
	 * Now that we have the from_elem figured out,
	 * check to see if we already have an inherit for this pairing
	 */
	while (III_NULL == inherit) {
		inherit = ipc_importance_inherit_find(from_elem, to_task_imp, depth);

		/* Do we have to allocate a new inherit */
		if (III_NULL == inherit) {
			if (III_NULL != alloc) {
				break;
			}

			/* allocate space */
			ipc_importance_unlock();
			alloc = (ipc_importance_inherit_t)
				zalloc(ipc_importance_inherit_zone);
			ipc_importance_lock();
		}
	}

	/* snapshot the donating status while we have importance locked */
	donating = ipc_importance_task_is_donor(from_task_imp);

	if (III_NULL != inherit) {
		/* We found one, piggyback on that */
		assert(0 < III_REFS(inherit));
		assert(0 < IIE_REFS(inherit->iii_from_elem));

		/* Take a reference for inherit */
		assert(III_REFS_MAX > III_REFS(inherit));
		ipc_importance_inherit_reference_internal(inherit);

		/* Reflect the inherit's change of status into the task boosts */
		if (0 == III_EXTERN(inherit)) {
			assert(!inherit->iii_donating);
			inherit->iii_donating = donating;
			if (donating) {
				to_task_imp->iit_externcnt += inherit->iii_externcnt;
				to_task_imp->iit_externdrop += inherit->iii_externdrop;
			}
		} else {
			assert(donating == inherit->iii_donating);
		}

		/* add in a external reference for this use of the inherit */
		inherit->iii_externcnt++;
	} else {
		/* initialize the previously allocated space */
		inherit = alloc;
		inherit->iii_bits = IIE_TYPE_INHERIT | 1;
		inherit->iii_made = 0;
		inherit->iii_externcnt = 1;
		inherit->iii_externdrop = 0;
		inherit->iii_depth = depth;
		inherit->iii_to_task = to_task_imp;
		inherit->iii_from_elem = IIE_NULL;
		queue_init(&inherit->iii_kmsgs);

		if (donating) {
			inherit->iii_donating = TRUE;
		} else {
			inherit->iii_donating = FALSE;
		}

		/*
		 * Chain our new inherit on the element it inherits from.
		 * The new inherit takes our reference on from_elem.
		 */
		ipc_importance_inherit_link(inherit, from_elem);

#if IIE_REF_DEBUG
		ipc_importance_counter_init(&inherit->iii_elem);
		from_elem->iie_kmsg_refs_inherited++;
		task_imp->iit_elem.iie_task_refs_inherited++;
#endif
	}

out_locked:

	/* If found inherit and donating, reflect that in the task externcnt */
	if (III_NULL != inherit && donating) {
		to_task_imp->iit_externcnt++;
		/* take the internal assertion */
		ipc_importance_task_hold_internal_assertion_locked(to_task_imp, 1);
		/* may have dropped and retaken importance lock */
	}

	/* If we didn't create a new inherit, we have some resources to release */
	if (III_NULL == inherit || inherit != alloc) {
		if (IIE_NULL != from_elem) {
			if (III_NULL != inherit) {
				incr_ref_counter(from_elem->iie_kmsg_refs_coalesced);
			} else {
				incr_ref_counter(from_elem->iie_kmsg_refs_dropped);
			}
			ipc_importance_release_locked(from_elem);
			/* importance unlocked */
		} else {
			ipc_importance_unlock();
		}

		if (IIT_NULL != to_task_imp) {
			if (III_NULL != inherit) {
				incr_ref_counter(to_task_imp->iit_elem.iie_task_refs_coalesced);
			}
			ipc_importance_task_release(to_task_imp);
		}

		if (III_NULL != alloc) {
			zfree(ipc_importance_inherit_zone, alloc);
		}
	} else {
		/* from_elem and to_task_imp references transferred to new inherit */
		ipc_importance_unlock();
	}

	return inherit;
}