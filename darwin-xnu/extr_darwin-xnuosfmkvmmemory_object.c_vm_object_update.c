#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_page_queue_entry_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  scalar_t__ vm_object_size_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  vm_fault_return_t ;
struct vm_object_fault_info {scalar_t__ cs_bypass; scalar_t__ pmap_cs_associated; scalar_t__ cluster_size; scalar_t__ stealth; scalar_t__ hi_offset; scalar_t__ lo_offset; int /*<<< orphan*/  behavior; int /*<<< orphan*/  interruptible; } ;
typedef  int /*<<< orphan*/  memory_object_return_t ;
typedef  int kern_return_t ;
typedef  int boolean_t ;
struct TYPE_24__ {scalar_t__ vo_shadow_offset; scalar_t__ vo_size; int resident_page_count; int /*<<< orphan*/  memq; int /*<<< orphan*/ * shadow; scalar_t__ shadowed; scalar_t__ shadow_severed; struct TYPE_24__* copy; } ;
struct TYPE_23__ {scalar_t__ vmp_offset; int /*<<< orphan*/  vmp_listq; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int KERN_SUCCESS ; 
 int MEMORY_OBJECT_COPY_SYNC ; 
 int MEMORY_OBJECT_DATA_FLUSH ; 
 int MEMORY_OBJECT_DATA_NO_CHANGE ; 
 int MEMORY_OBJECT_DATA_PURGE ; 
 int MEMORY_OBJECT_DATA_SYNC ; 
 int MEMORY_OBJECT_IO_SYNC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_BEHAVIOR_SEQUENTIAL ; 
#define  VM_FAULT_INTERRUPTED 133 
#define  VM_FAULT_MEMORY_ERROR 132 
#define  VM_FAULT_MEMORY_SHORTAGE 131 
#define  VM_FAULT_RETRY 130 
#define  VM_FAULT_SUCCESS 129 
#define  VM_FAULT_SUCCESS_NO_VM_PAGE 128 
 TYPE_2__* VM_OBJECT_NULL ; 
 int /*<<< orphan*/  VM_PAGE_NON_SPECULATIVE_PAGEABLE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_WAIT () ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int atop_64 (scalar_t__) ; 
 int /*<<< orphan*/  mutex_pause (int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault_cleanup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_fault_page (TYPE_2__*,scalar_t__,int,scalar_t__,scalar_t__,int*,TYPE_1__**,TYPE_1__**,int*,int*,scalar_t__,scalar_t__,struct vm_object_fault_info*) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_2__*) ; 
 scalar_t__ vm_object_lock_try (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_paging_begin (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_paging_end (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_reference_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 scalar_t__ vm_object_update_extent (TYPE_2__*,scalar_t__,scalar_t__,scalar_t__*,int*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vm_page_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

kern_return_t
vm_object_update(
	vm_object_t		object,
	vm_object_offset_t	offset,
	vm_object_size_t	size,
	vm_object_offset_t	*resid_offset,
	int			*io_errno,
	memory_object_return_t	should_return,
	int			flags,
	vm_prot_t		protection)
{
        vm_object_t		copy_object = VM_OBJECT_NULL;
	boolean_t		data_returned = FALSE;
	boolean_t		update_cow;
	boolean_t		should_flush = (flags & MEMORY_OBJECT_DATA_FLUSH) ? TRUE : FALSE;
	boolean_t		should_iosync = (flags & MEMORY_OBJECT_IO_SYNC) ? TRUE : FALSE;
	vm_fault_return_t	result;
	int			num_of_extents;
	int			n;
#define MAX_EXTENTS	8
#define EXTENT_SIZE	(1024 * 1024 * 256)
#define RESIDENT_LIMIT	(1024 * 32)
	struct extent {
	        vm_object_offset_t e_base;
	        vm_object_offset_t e_min;
	        vm_object_offset_t e_max;
	} extents[MAX_EXTENTS];

	/*
	 *	To avoid blocking while scanning for pages, save
	 *	dirty pages to be cleaned all at once.
	 *
	 *	XXXO A similar strategy could be used to limit the
	 *	number of times that a scan must be restarted for
	 *	other reasons.  Those pages that would require blocking
	 *	could be temporarily collected in another list, or
	 *	their offsets could be recorded in a small array.
	 */

	/*
	 * XXX	NOTE: May want to consider converting this to a page list
	 * XXX	vm_map_copy interface.  Need to understand object
	 * XXX	coalescing implications before doing so.
	 */

	update_cow = ((flags & MEMORY_OBJECT_DATA_FLUSH) 
			&& (!(flags & MEMORY_OBJECT_DATA_NO_CHANGE) &&
					!(flags & MEMORY_OBJECT_DATA_PURGE)))
				|| (flags & MEMORY_OBJECT_COPY_SYNC);
			
	if (update_cow || (flags & (MEMORY_OBJECT_DATA_PURGE | MEMORY_OBJECT_DATA_SYNC))) {
	        int collisions = 0;

	        while ((copy_object = object->copy) != VM_OBJECT_NULL) {
		        /*
			 * need to do a try here since we're swimming upstream
			 * against the normal lock ordering... however, we need
			 * to hold the object stable until we gain control of the
			 * copy object so we have to be careful how we approach this
			 */
		        if (vm_object_lock_try(copy_object)) {
			       /*
				* we 'won' the lock on the copy object...
				* no need to hold the object lock any longer...
				* take a real reference on the copy object because
				* we're going to call vm_fault_page on it which may
				* under certain conditions drop the lock and the paging
				* reference we're about to take... the reference
				* will keep the copy object from going away if that happens
				*/
			       vm_object_unlock(object);
			       vm_object_reference_locked(copy_object);
			       break;
			}
			vm_object_unlock(object);

			collisions++;
			mutex_pause(collisions);

			vm_object_lock(object);
		}
	}
	if ((copy_object != VM_OBJECT_NULL && update_cow) || (flags & MEMORY_OBJECT_DATA_SYNC)) {
		vm_map_size_t		i;
		vm_map_size_t		copy_size;
		vm_map_offset_t		copy_offset;
		vm_prot_t		prot;
		vm_page_t		page;
		vm_page_t		top_page;
		kern_return_t		error = 0;
		struct vm_object_fault_info fault_info = {};

		if (copy_object != VM_OBJECT_NULL) {
		        /*
			 * translate offset with respect to shadow's offset
			 */
		        copy_offset = (offset >= copy_object->vo_shadow_offset) ?
			  (vm_map_offset_t)(offset - copy_object->vo_shadow_offset) :
			  (vm_map_offset_t) 0;

			if (copy_offset > copy_object->vo_size)
			        copy_offset = copy_object->vo_size;

			/*
			 * clip size with respect to shadow offset
			 */
			if (offset >= copy_object->vo_shadow_offset) {
			        copy_size = size;
			} else if (size >= copy_object->vo_shadow_offset - offset) {
			        copy_size = size - (copy_object->vo_shadow_offset - offset);
			} else {
			        copy_size = 0;
			}
			
			if (copy_offset + copy_size > copy_object->vo_size) {
			        if (copy_object->vo_size >= copy_offset) {
				        copy_size = copy_object->vo_size - copy_offset;
				} else {
				        copy_size = 0;
				}
			}
			copy_size+=copy_offset;

		} else {
			copy_object = object;

			copy_size   = offset + size;
			copy_offset = offset;
		}
		fault_info.interruptible = THREAD_UNINT;
		fault_info.behavior  = VM_BEHAVIOR_SEQUENTIAL;
		fault_info.lo_offset = copy_offset;
		fault_info.hi_offset = copy_size;
		fault_info.stealth = TRUE;
		assert(fault_info.cs_bypass == FALSE);
		assert(fault_info.pmap_cs_associated == FALSE);

		vm_object_paging_begin(copy_object);

		for (i = copy_offset; i < copy_size; i += PAGE_SIZE) {
	RETRY_COW_OF_LOCK_REQUEST:
			fault_info.cluster_size = (vm_size_t) (copy_size - i);
			assert(fault_info.cluster_size == copy_size - i);

			prot = 	VM_PROT_WRITE|VM_PROT_READ;
			page = VM_PAGE_NULL;
			result = vm_fault_page(copy_object, i, 
					       VM_PROT_WRITE|VM_PROT_READ,
					       FALSE,
					       FALSE, /* page not looked up */
					       &prot,
					       &page,
					       &top_page,
					       (int *)0,
					       &error,
					       FALSE,
					       FALSE, &fault_info);

			switch (result) {
			case VM_FAULT_SUCCESS:
				if (top_page) {
					vm_fault_cleanup(
						VM_PAGE_OBJECT(page), top_page);
					vm_object_lock(copy_object);
					vm_object_paging_begin(copy_object);
				}
				if (( !VM_PAGE_NON_SPECULATIVE_PAGEABLE(page))) {

					vm_page_lockspin_queues();
					
					if (( !VM_PAGE_NON_SPECULATIVE_PAGEABLE(page))) {
						vm_page_deactivate(page);
					}
					vm_page_unlock_queues();
				}
				PAGE_WAKEUP_DONE(page);
				break;
			case VM_FAULT_RETRY:
				prot = 	VM_PROT_WRITE|VM_PROT_READ;
				vm_object_lock(copy_object);
				vm_object_paging_begin(copy_object);
				goto RETRY_COW_OF_LOCK_REQUEST;
			case VM_FAULT_INTERRUPTED:
				prot = 	VM_PROT_WRITE|VM_PROT_READ;
				vm_object_lock(copy_object);
				vm_object_paging_begin(copy_object);
				goto RETRY_COW_OF_LOCK_REQUEST;
			case VM_FAULT_MEMORY_SHORTAGE:
				VM_PAGE_WAIT();
				prot = 	VM_PROT_WRITE|VM_PROT_READ;
				vm_object_lock(copy_object);
				vm_object_paging_begin(copy_object);
				goto RETRY_COW_OF_LOCK_REQUEST;
			case VM_FAULT_SUCCESS_NO_VM_PAGE:
				/* success but no VM page: fail */
				vm_object_paging_end(copy_object);
				vm_object_unlock(copy_object);
				/*FALLTHROUGH*/
			case VM_FAULT_MEMORY_ERROR:
			        if (object != copy_object)
				        vm_object_deallocate(copy_object);
				vm_object_lock(object);
				goto BYPASS_COW_COPYIN;
			default:
				panic("vm_object_update: unexpected error 0x%x"
				      " from vm_fault_page()\n", result);
			}

		}
		vm_object_paging_end(copy_object);
	}
	if ((flags & (MEMORY_OBJECT_DATA_SYNC | MEMORY_OBJECT_COPY_SYNC))) {
	        if (copy_object != VM_OBJECT_NULL && copy_object != object) {
			vm_object_unlock(copy_object);
		        vm_object_deallocate(copy_object);
			vm_object_lock(object);
		}
		return KERN_SUCCESS;
	}
	if (copy_object != VM_OBJECT_NULL && copy_object != object) {
	        if ((flags & MEMORY_OBJECT_DATA_PURGE)) {
			vm_object_lock_assert_exclusive(copy_object);
		        copy_object->shadow_severed = TRUE;
			copy_object->shadowed = FALSE;
			copy_object->shadow = NULL;
			/*
			 * delete the ref the COW was holding on the target object
			 */
			vm_object_deallocate(object);
		}
		vm_object_unlock(copy_object);
	        vm_object_deallocate(copy_object);
		vm_object_lock(object);
	}
BYPASS_COW_COPYIN:

	/*
	 * when we have a really large range to check relative
	 * to the number of actual resident pages, we'd like
	 * to use the resident page list to drive our checks
	 * however, the object lock will get dropped while processing
	 * the page which means the resident queue can change which
	 * means we can't walk the queue as we process the pages
	 * we also want to do the processing in offset order to allow
	 * 'runs' of pages to be collected if we're being told to 
	 * flush to disk... the resident page queue is NOT ordered.
	 * 
	 * a temporary solution (until we figure out how to deal with
	 * large address spaces more generically) is to pre-flight
	 * the resident page queue (if it's small enough) and develop
	 * a collection of extents (that encompass actual resident pages)
	 * to visit.  This will at least allow us to deal with some of the
	 * more pathological cases in a more efficient manner.  The current
	 * worst case (a single resident page at the end of an extremely large
	 * range) can take minutes to complete for ranges in the terrabyte
	 * category... since this routine is called when truncating a file,
	 * and we currently support files up to 16 Tbytes in size, this
	 * is not a theoretical problem
	 */

	if ((object->resident_page_count < RESIDENT_LIMIT) && 
	    (atop_64(size) > (unsigned)(object->resident_page_count/(8 * MAX_EXTENTS)))) {
		vm_page_t		next;
		vm_object_offset_t	start;
		vm_object_offset_t	end;
		vm_object_size_t	e_mask;
		vm_page_t               m;

		start = offset;
		end   = offset + size;
		num_of_extents = 0;
		e_mask = ~((vm_object_size_t)(EXTENT_SIZE - 1));

		m = (vm_page_t) vm_page_queue_first(&object->memq);

		while (!vm_page_queue_end(&object->memq, (vm_page_queue_entry_t) m)) {
			next = (vm_page_t) vm_page_queue_next(&m->vmp_listq);

			if ((m->vmp_offset >= start) && (m->vmp_offset < end)) {
			        /*
				 * this is a page we're interested in
				 * try to fit it into a current extent
				 */
			        for (n = 0; n < num_of_extents; n++) {
				        if ((m->vmp_offset & e_mask) == extents[n].e_base) {
					        /*
						 * use (PAGE_SIZE - 1) to determine the
						 * max offset so that we don't wrap if
						 * we're at the last page of the space
						 */
					        if (m->vmp_offset < extents[n].e_min)
						        extents[n].e_min = m->vmp_offset;
						else if ((m->vmp_offset + (PAGE_SIZE - 1)) > extents[n].e_max)
						        extents[n].e_max = m->vmp_offset + (PAGE_SIZE - 1);
					        break;
					}
				}
				if (n == num_of_extents) {
				        /*
					 * didn't find a current extent that can encompass
					 * this page
					 */
				        if (n < MAX_EXTENTS) {
					        /*
						 * if we still have room, 
						 * create a new extent
						 */
					        extents[n].e_base = m->vmp_offset & e_mask;
						extents[n].e_min  = m->vmp_offset;
						extents[n].e_max  = m->vmp_offset + (PAGE_SIZE - 1);

						num_of_extents++;
					} else {
						/*
						 * no room to create a new extent...
						 * fall back to a single extent based
						 * on the min and max page offsets 
						 * we find in the range we're interested in...
						 * first, look through the extent list and
						 * develop the overall min and max for the
						 * pages we've looked at up to this point
						 */						
					        for (n = 1; n < num_of_extents; n++) {
						        if (extents[n].e_min < extents[0].e_min)
						                extents[0].e_min = extents[n].e_min;
							if (extents[n].e_max > extents[0].e_max)
						                extents[0].e_max = extents[n].e_max;
						}
						/*
						 * now setup to run through the remaining pages
						 * to determine the overall min and max
						 * offset for the specified range
						 */
						extents[0].e_base = 0;
						e_mask = 0;
						num_of_extents = 1;

						/*
						 * by continuing, we'll reprocess the
						 * page that forced us to abandon trying
						 * to develop multiple extents
						 */
						continue;
					}
				}
			}
			m = next;
		}
	} else {
	        extents[0].e_min = offset;
		extents[0].e_max = offset + (size - 1);

		num_of_extents = 1;
	}
	for (n = 0; n < num_of_extents; n++) {
	        if (vm_object_update_extent(object, extents[n].e_min, extents[n].e_max, resid_offset, io_errno,
					    should_flush, should_return, should_iosync, protection))
		        data_returned = TRUE;
	}
	return (data_returned);
}