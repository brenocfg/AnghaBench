#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
struct TYPE_22__ {int pageout; scalar_t__ ref_count; scalar_t__ paging_in_progress; scalar_t__ activity_in_progress; scalar_t__ resident_page_count; scalar_t__ vo_shadow_offset; int /*<<< orphan*/  memq; struct TYPE_22__* shadow; } ;
struct TYPE_21__ {int vmp_private; int vmp_free_when_done; int vmp_dirty; int vmp_busy; scalar_t__ vmp_q_state; int vmp_wire_count; int vmp_overwriting; void* vmp_cleaning; void* vmp_absent; scalar_t__ vmp_reference; scalar_t__ vmp_precious; scalar_t__ vmp_offset; int /*<<< orphan*/  vmp_laundry; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  PAGE_WAKEUP (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_MEM_MODIFIED ; 
 int /*<<< orphan*/  VM_PAGE_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_IS_WIRED ; 
 scalar_t__ VM_PAGE_NOT_ON_Q ; 
 TYPE_1__* VM_PAGE_NULL ; 
 scalar_t__ VM_PAGE_ON_PAGEOUT_Q ; 
 int VM_PAGE_WIRED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_STAT_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pmap_clear_modify (int /*<<< orphan*/ ) ; 
 int pmap_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reactivations ; 
 int /*<<< orphan*/  vm_object_activity_end (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock_queues () ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_queue_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_page_unwire (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_pageout_throttle_up (TYPE_1__*) ; 

void
vm_pageout_object_terminate(
	vm_object_t	object)
{
	vm_object_t	shadow_object;

	/*
	 * Deal with the deallocation (last reference) of a pageout object
	 * (used for cleaning-in-place) by dropping the paging references/
	 * freeing pages in the original object.
	 */

	assert(object->pageout);
	shadow_object = object->shadow;
	vm_object_lock(shadow_object);

	while (!vm_page_queue_empty(&object->memq)) {
		vm_page_t 		p, m;
		vm_object_offset_t	offset;

		p = (vm_page_t) vm_page_queue_first(&object->memq);

		assert(p->vmp_private);
		assert(p->vmp_free_when_done);
		p->vmp_free_when_done = FALSE;
		assert(!p->vmp_cleaning);
		assert(!p->vmp_laundry);

		offset = p->vmp_offset;
		VM_PAGE_FREE(p);
		p = VM_PAGE_NULL;

		m = vm_page_lookup(shadow_object,
			offset + object->vo_shadow_offset);

		if(m == VM_PAGE_NULL)
			continue;

		assert((m->vmp_dirty) || (m->vmp_precious) ||
				(m->vmp_busy && m->vmp_cleaning));

		/*
		 * Handle the trusted pager throttle.
		 * Also decrement the burst throttle (if external).
		 */
		vm_page_lock_queues();
		if (m->vmp_q_state == VM_PAGE_ON_PAGEOUT_Q)
			vm_pageout_throttle_up(m);

		/*
		 * Handle the "target" page(s). These pages are to be freed if
		 * successfully cleaned. Target pages are always busy, and are
		 * wired exactly once. The initial target pages are not mapped,
		 * (so cannot be referenced or modified) but converted target
		 * pages may have been modified between the selection as an
		 * adjacent page and conversion to a target.
		 */
		if (m->vmp_free_when_done) {
			assert(m->vmp_busy);
			assert(m->vmp_q_state == VM_PAGE_IS_WIRED);
			assert(m->vmp_wire_count == 1);
			m->vmp_cleaning = FALSE;
			m->vmp_free_when_done = FALSE;
			/*
			 * Revoke all access to the page. Since the object is
			 * locked, and the page is busy, this prevents the page
			 * from being dirtied after the pmap_disconnect() call
			 * returns.
			 *
			 * Since the page is left "dirty" but "not modifed", we
			 * can detect whether the page was redirtied during
			 * pageout by checking the modify state.
			 */
			if (pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(m)) & VM_MEM_MODIFIED) {
				SET_PAGE_DIRTY(m, FALSE);
			} else {
				m->vmp_dirty = FALSE;
			}

			if (m->vmp_dirty) {
				vm_page_unwire(m, TRUE);	/* reactivates */
				VM_STAT_INCR(reactivations);
				PAGE_WAKEUP_DONE(m);
			} else {
			        vm_page_free(m);  /* clears busy, etc. */
			}
			vm_page_unlock_queues();
			continue;
		}
		/*
		 * Handle the "adjacent" pages. These pages were cleaned in
		 * place, and should be left alone.
		 * If prep_pin_count is nonzero, then someone is using the
		 * page, so make it active.
		 */
		if ((m->vmp_q_state == VM_PAGE_NOT_ON_Q) && !m->vmp_private) {
			if (m->vmp_reference)
				vm_page_activate(m);
			else
				vm_page_deactivate(m);
		}
		if (m->vmp_overwriting) {
			/*
			 * the (COPY_OUT_FROM == FALSE) request_page_list case
			 */
			if (m->vmp_busy) {
				/*
				 * We do not re-set m->vmp_dirty !
				 * The page was busy so no extraneous activity
				 * could have occurred. COPY_INTO is a read into the
				 * new pages. CLEAN_IN_PLACE does actually write
				 * out the pages but handling outside of this code
				 * will take care of resetting dirty. We clear the
				 * modify however for the Programmed I/O case.
				 */
				pmap_clear_modify(VM_PAGE_GET_PHYS_PAGE(m));

				m->vmp_busy = FALSE;
				m->vmp_absent = FALSE;
			} else {
				/*
				 * alternate (COPY_OUT_FROM == FALSE) request_page_list case
				 * Occurs when the original page was wired
				 * at the time of the list request
				 */
				 assert(VM_PAGE_WIRED(m));
				 vm_page_unwire(m, TRUE);	/* reactivates */
			}
			m->vmp_overwriting = FALSE;
		} else {
			m->vmp_dirty = FALSE;
		}
		m->vmp_cleaning = FALSE;

		/*
		 * Wakeup any thread waiting for the page to be un-cleaning.
		 */
		PAGE_WAKEUP(m);
		vm_page_unlock_queues();
	}
	/*
	 * Account for the paging reference taken in vm_paging_object_allocate.
	 */
	vm_object_activity_end(shadow_object);
	vm_object_unlock(shadow_object);

	assert(object->ref_count == 0);
	assert(object->paging_in_progress == 0);
	assert(object->activity_in_progress == 0);
	assert(object->resident_page_count == 0);
	return;
}