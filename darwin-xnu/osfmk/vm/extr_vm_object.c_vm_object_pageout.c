#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_page_queue_entry_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
struct vm_pageout_queue {int /*<<< orphan*/  pgo_laundry; scalar_t__ pgo_draining; } ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_16__ {scalar_t__ pager; int /*<<< orphan*/  memq; int /*<<< orphan*/  pager_initialized; int /*<<< orphan*/  alive; scalar_t__ terminating; int /*<<< orphan*/  internal; } ;
struct TYPE_15__ {scalar_t__ vmp_q_state; scalar_t__ vmp_pmapped; scalar_t__ vmp_precious; scalar_t__ vmp_dirty; scalar_t__ vmp_cleaning; scalar_t__ vmp_error; int /*<<< orphan*/  vmp_unusual; scalar_t__ vmp_absent; scalar_t__ vmp_busy; scalar_t__ vmp_fictitious; scalar_t__ vmp_laundry; int /*<<< orphan*/  vmp_listq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int PMAP_OPTIONS_COMPRESSOR ; 
 int PMAP_OPTIONS_COMPRESSOR_IFF_MODIFIED ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_INTERRUPTIBLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 int VM_MEM_MODIFIED ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGE_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_ON_FREE_Q ; 
 scalar_t__ VM_PAGE_ON_THROTTLED_Q ; 
 scalar_t__ VM_PAGE_Q_THROTTLED (struct vm_pageout_queue*) ; 
 scalar_t__ VM_PAGE_WIRED (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_disconnect_options (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_compressor_low_on_space () ; 
 int /*<<< orphan*/  vm_object_collapse (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_compressor_pager_create (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_queues_remove (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_pageout_cluster (TYPE_1__*) ; 
 struct vm_pageout_queue vm_pageout_queue_internal ; 

void
vm_object_pageout(
	vm_object_t object)
{
	vm_page_t 			p, next;
	struct	vm_pageout_queue 	*iq;

	if (!VM_CONFIG_COMPRESSOR_IS_PRESENT)
		return;

	iq = &vm_pageout_queue_internal;
	
	assert(object != VM_OBJECT_NULL );
	
	vm_object_lock(object);

	if (!object->internal ||
	    object->terminating ||
	    !object->alive) {
		vm_object_unlock(object);
		return;
	}

	if (!object->pager_initialized || object->pager == MEMORY_OBJECT_NULL)  {
			
		if (!object->pager_initialized) {

			vm_object_collapse(object, (vm_object_offset_t) 0, TRUE);

			if (!object->pager_initialized)
				vm_object_compressor_pager_create(object);
		}

		if (!object->pager_initialized || object->pager == MEMORY_OBJECT_NULL)  {
			vm_object_unlock(object);
			return;
		}
	}
			
ReScan:	
	next = (vm_page_t)vm_page_queue_first(&object->memq);

	while (!vm_page_queue_end(&object->memq, (vm_page_queue_entry_t)next)) {
		p = next;
		next = (vm_page_t)vm_page_queue_next(&next->vmp_listq);
		
		assert(p->vmp_q_state != VM_PAGE_ON_FREE_Q);
		
		if ((p->vmp_q_state == VM_PAGE_ON_THROTTLED_Q) ||
		    p->vmp_cleaning ||
		    p->vmp_laundry ||
		    p->vmp_busy ||
		    p->vmp_absent ||
		    p->vmp_error ||
		    p->vmp_fictitious ||
		    VM_PAGE_WIRED(p)) {
			/*
			 * Page is already being cleaned or can't be cleaned.
			 */
			continue;
		}
		if (vm_compressor_low_on_space()) {
			break;		
		}

		/* Throw to the pageout queue */

		vm_page_lockspin_queues();

		if (VM_PAGE_Q_THROTTLED(iq)) {
					
			iq->pgo_draining = TRUE;
					
			assert_wait((event_t) (&iq->pgo_laundry + 1),
				    THREAD_INTERRUPTIBLE);
			vm_page_unlock_queues();
			vm_object_unlock(object);
					
			thread_block(THREAD_CONTINUE_NULL);

			vm_object_lock(object);
			goto ReScan;
		}

		assert(!p->vmp_fictitious);
		assert(!p->vmp_busy);
		assert(!p->vmp_absent);
		assert(!p->vmp_unusual);
		assert(!p->vmp_error);
		assert(!VM_PAGE_WIRED(p));
		assert(!p->vmp_cleaning);

		if (p->vmp_pmapped == TRUE) {
			int refmod_state;
			int pmap_options;

			/*
			 * Tell pmap the page should be accounted
			 * for as "compressed" if it's been modified.
			 */
			pmap_options =
				PMAP_OPTIONS_COMPRESSOR_IFF_MODIFIED;
			if (p->vmp_dirty || p->vmp_precious) {
				/*
				 * We already know it's been modified,
				 * so tell pmap to account for it
				 * as "compressed".
				 */
				pmap_options = PMAP_OPTIONS_COMPRESSOR;
			}
			refmod_state = pmap_disconnect_options(VM_PAGE_GET_PHYS_PAGE(p),
							       pmap_options,
							       NULL);
			if (refmod_state & VM_MEM_MODIFIED) {
				SET_PAGE_DIRTY(p, FALSE);
			}
		}

		if (!p->vmp_dirty && !p->vmp_precious) {
			vm_page_unlock_queues();
			VM_PAGE_FREE(p);
			continue;
		}
		vm_page_queues_remove(p, TRUE);

		vm_pageout_cluster(p);
		
		vm_page_unlock_queues();
	}
	vm_object_unlock(object);
}