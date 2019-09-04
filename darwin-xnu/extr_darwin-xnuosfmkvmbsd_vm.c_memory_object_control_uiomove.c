#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  memory_object_offset_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  int addr64_t ;
struct TYPE_19__ {scalar_t__ pager; struct TYPE_19__* copy; int /*<<< orphan*/  internal; } ;
struct TYPE_18__ {scalar_t__ vmp_dirty; scalar_t__ vmp_clustered; scalar_t__ vmp_busy; scalar_t__ vmp_cs_validated; int /*<<< orphan*/  vmp_cs_tainted; scalar_t__ vmp_laundry; scalar_t__ vmp_cleaning; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAX_RUN ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int /*<<< orphan*/  PAGE_SLEEP (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_PAGE_DIRTY (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  TASK_WRITE_DEFERRED ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 TYPE_2__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGEOUT_DEBUG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_PAGE_CONSUME_CLUSTERED (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_task () ; 
 TYPE_2__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  task_update_logical_writes (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uiomove64 (int,int,void*) ; 
 int /*<<< orphan*/  vm_cs_validated_resets ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_lru (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_pageout_steal_laundry (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vnode_pager_lookup_vnode (scalar_t__) ; 

int
memory_object_control_uiomove(
	memory_object_control_t	control,
	memory_object_offset_t	offset,
	void		*	uio,
	int			start_offset,
	int			io_requested,
	int			mark_dirty,
	int			take_reference)
{
	vm_object_t		object;
	vm_page_t		dst_page;
	int			xsize;
	int			retval = 0;
	int			cur_run;
	int			cur_needed;
	int			i;
	int			orig_offset;
	vm_page_t		page_run[MAX_RUN];
	int 			dirty_count;	/* keeps track of number of pages dirtied as part of this uiomove */

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL) {
		return (0);
	}
	assert(!object->internal);

	vm_object_lock(object);

	if (mark_dirty && object->copy != VM_OBJECT_NULL) {
		/*
		 * We can't modify the pages without honoring
		 * copy-on-write obligations first, so fall off
		 * this optimized path and fall back to the regular
		 * path.
		 */
		vm_object_unlock(object);
		return 0;
	}
	orig_offset = start_offset;

	dirty_count = 0;	
	while (io_requested && retval == 0) {

		cur_needed = (start_offset + io_requested + (PAGE_SIZE - 1)) / PAGE_SIZE;

		if (cur_needed > MAX_RUN)
		        cur_needed = MAX_RUN;
		
		for (cur_run = 0; cur_run < cur_needed; ) {

		        if ((dst_page = vm_page_lookup(object, offset)) == VM_PAGE_NULL)
			        break;


			if (dst_page->vmp_busy || dst_page->vmp_cleaning) {
				/*
				 * someone else is playing with the page... if we've
				 * already collected pages into this run, go ahead
				 * and process now, we can't block on this
				 * page while holding other pages in the BUSY state
				 * otherwise we will wait
				 */
				if (cur_run)
					break;
				PAGE_SLEEP(object, dst_page, THREAD_UNINT);
				continue;
			}
			if (dst_page->vmp_laundry)
				vm_pageout_steal_laundry(dst_page, FALSE);

		        if (mark_dirty) {
				if (dst_page->vmp_dirty == FALSE)
					dirty_count++;
				SET_PAGE_DIRTY(dst_page, FALSE);
				if (dst_page->vmp_cs_validated && 
				    !dst_page->vmp_cs_tainted) {
					/*
					 * CODE SIGNING:
					 * We're modifying a code-signed
					 * page: force revalidate
					 */
					dst_page->vmp_cs_validated = FALSE;

					VM_PAGEOUT_DEBUG(vm_cs_validated_resets, 1);

					pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(dst_page));
				}
			}
			dst_page->vmp_busy = TRUE;

			page_run[cur_run++] = dst_page;

			offset += PAGE_SIZE_64;
		}
		if (cur_run == 0)
		        /*
			 * we hit a 'hole' in the cache or
			 * a page we don't want to try to handle,
			 * so bail at this point
			 * we'll unlock the object below
			 */
		        break;
		vm_object_unlock(object);

		for (i = 0; i < cur_run; i++) {
		  
		        dst_page = page_run[i];

			if ((xsize = PAGE_SIZE - start_offset) > io_requested)
			        xsize = io_requested;

			if ( (retval = uiomove64((addr64_t)(((addr64_t)(VM_PAGE_GET_PHYS_PAGE(dst_page)) << PAGE_SHIFT) + start_offset), xsize, uio)) )
			        break;

			io_requested -= xsize;
			start_offset = 0;
		}
		vm_object_lock(object);

		/*
		 * if we have more than 1 page to work on
		 * in the current run, or the original request
		 * started at offset 0 of the page, or we're
		 * processing multiple batches, we will move
		 * the pages to the tail of the inactive queue
		 * to implement an LRU for read/write accesses
		 *
		 * the check for orig_offset == 0 is there to 
		 * mitigate the cost of small (< page_size) requests
		 * to the same page (this way we only move it once)
		 */
		if (take_reference && (cur_run > 1 || orig_offset == 0)) {

			vm_page_lockspin_queues();

			for (i = 0; i < cur_run; i++)
				vm_page_lru(page_run[i]);

			vm_page_unlock_queues();
		}
		for (i = 0; i < cur_run; i++) {
		        dst_page = page_run[i];

			/*
			 * someone is explicitly referencing this page...
			 * update clustered and speculative state
			 * 
			 */
			if (dst_page->vmp_clustered)
				VM_PAGE_CONSUME_CLUSTERED(dst_page);

			PAGE_WAKEUP_DONE(dst_page);
		}
		orig_offset = 0;
	}
	if (object->pager)
		task_update_logical_writes(current_task(), (dirty_count * PAGE_SIZE), TASK_WRITE_DEFERRED, vnode_pager_lookup_vnode(object->pager));
	vm_object_unlock(object);
	return (retval);
}