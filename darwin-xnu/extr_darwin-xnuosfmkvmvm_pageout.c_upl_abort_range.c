#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int* wpl_array_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int vm_object_offset_t ;
typedef  TYPE_3__* upl_t ;
typedef  int upl_size_t ;
struct TYPE_34__ {void* needed; } ;
typedef  TYPE_4__ upl_page_info_t ;
typedef  int upl_offset_t ;
struct vm_page_delayed_work {int dw_mask; } ;
struct upl {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  void* boolean_t ;
struct TYPE_33__ {int flags; int size; int offset; TYPE_2__* map_object; } ;
struct TYPE_32__ {int blocked_access; int paging_offset; int vo_shadow_offset; int /*<<< orphan*/  memq; struct TYPE_32__* shadow; } ;
struct TYPE_31__ {scalar_t__ vmp_q_state; int vmp_absent; int vmp_overwriting; int vmp_busy; void* vmp_cleaning; void* vmp_free_when_done; scalar_t__ vmp_laundry; scalar_t__ vmp_clustered; void* vmp_unusual; void* vmp_error; void* vmp_restart; } ;

/* Variables and functions */
 int DEFAULT_DELAYED_WORK_LIMIT ; 
 int DELAYED_WORK_LIMIT (int) ; 
 int DW_PAGE_WAKEUP ; 
 int DW_clear_busy ; 
 int DW_vm_page_activate ; 
 int DW_vm_page_deactivate_internal ; 
 int DW_vm_page_free ; 
 int DW_vm_page_lru ; 
 int DW_vm_page_unwire ; 
 int DW_vm_pageout_throttle_up ; 
 void* FALSE ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 scalar_t__ PAGE_SIZE_64 ; 
 int /*<<< orphan*/  PAGE_WAKEUP (TYPE_1__*) ; 
 void* TRUE ; 
 int UPL_ABORT_DUMP_PAGES ; 
 int UPL_ABORT_ERROR ; 
 int UPL_ABORT_REFERENCE ; 
 int UPL_ABORT_RESTART ; 
 int UPL_ABORT_UNAVAILABLE ; 
 int UPL_ACCESS_BLOCKED ; 
 int /*<<< orphan*/  UPL_COMMIT_FREE_ABSENT ; 
 int UPL_COMMIT_NOTIFY_EMPTY ; 
 int UPL_DEVICE_MEMORY ; 
 int UPL_INTERNAL ; 
 int UPL_IO_WIRE ; 
 int UPL_KERNEL_OBJECT ; 
 int UPL_LITE ; 
 TYPE_3__* UPL_NULL ; 
 int UPL_SHADOWED ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_OBJECT_EVENT_UNBLOCKED ; 
 int /*<<< orphan*/  VM_PAGE_ADD_DELAYED_WORK (struct vm_page_delayed_work*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  VM_PAGE_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PAGE_PAGEABLE (TYPE_1__*) ; 
 scalar_t__ VM_PAGE_USED_BY_COMPRESSOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upl_commit_range (TYPE_3__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  upl_deallocate (TYPE_3__*) ; 
 int /*<<< orphan*/  upl_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  upl_unlock (TYPE_3__*) ; 
 int vector_upl_is_valid (TYPE_3__*) ; 
 void* vector_upl_set_subupl (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vector_upl_subupl_byoffset (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  vm_object_activity_end (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_collapse (TYPE_2__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock_shared (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_wakeup (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_do_delayed_work (TYPE_2__*,int /*<<< orphan*/ ,struct vm_page_delayed_work*,int) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,int) ; 
 scalar_t__ vm_page_queue_empty (int /*<<< orphan*/ *) ; 

kern_return_t
upl_abort_range(
	upl_t			upl,
	upl_offset_t		offset,
	upl_size_t		size,
	int			error,
	boolean_t		*empty)
{
	upl_page_info_t		*user_page_list = NULL;
	upl_size_t		xfer_size, subupl_size = size;
	vm_object_t		shadow_object;
	vm_object_t		object;
	vm_object_offset_t	target_offset;
	upl_offset_t		subupl_offset = offset;
	int			entry;
	wpl_array_t 	 	lite_list;
	int			occupied;
	struct	vm_page_delayed_work	dw_array[DEFAULT_DELAYED_WORK_LIMIT];
	struct	vm_page_delayed_work	*dwp;
	int			dw_count;
	int			dw_limit;
	int			isVectorUPL = 0;
	upl_t			vector_upl = NULL;

	*empty = FALSE;

	if (upl == UPL_NULL)
		return KERN_INVALID_ARGUMENT;

	if ( (upl->flags & UPL_IO_WIRE) && !(error & UPL_ABORT_DUMP_PAGES) )
		return upl_commit_range(upl, offset, size, UPL_COMMIT_FREE_ABSENT, NULL, 0, empty);

	if((isVectorUPL = vector_upl_is_valid(upl))) {
		vector_upl = upl;
		upl_lock(vector_upl);
	}
	else
		upl_lock(upl);

process_upl_to_abort:
	if(isVectorUPL) {
		size = subupl_size;
		offset = subupl_offset;
		if(size == 0) {
			upl_unlock(vector_upl);
			return KERN_SUCCESS;
		}
		upl =  vector_upl_subupl_byoffset(vector_upl, &offset, &size);
		if(upl == NULL) {
			upl_unlock(vector_upl);
			return KERN_FAILURE;
		}
		subupl_size -= size;
		subupl_offset += size;
	}

	*empty = FALSE;

#if UPL_DEBUG
	if (upl->upl_commit_index < UPL_DEBUG_COMMIT_RECORDS) {
		(void) OSBacktrace(&upl->upl_commit_records[upl->upl_commit_index].c_retaddr[0], UPL_DEBUG_STACK_FRAMES);

		upl->upl_commit_records[upl->upl_commit_index].c_beg = offset;
		upl->upl_commit_records[upl->upl_commit_index].c_end = (offset + size);
		upl->upl_commit_records[upl->upl_commit_index].c_aborted = 1;

		upl->upl_commit_index++;
	}
#endif
	if (upl->flags & UPL_DEVICE_MEMORY)
		xfer_size = 0;
	else if ((offset + size) <= upl->size)
	        xfer_size = size;
	else {
		if(!isVectorUPL)
			upl_unlock(upl);
		else {
			upl_unlock(vector_upl);
		}

		return KERN_FAILURE;
	}
	if (upl->flags & UPL_INTERNAL) {
		lite_list = (wpl_array_t)
			((((uintptr_t)upl) + sizeof(struct upl))
			+ ((upl->size/PAGE_SIZE) * sizeof(upl_page_info_t)));

		user_page_list = (upl_page_info_t *) (((uintptr_t)upl) + sizeof(struct upl));
	} else {
		lite_list = (wpl_array_t)
			(((uintptr_t)upl) + sizeof(struct upl));
	}
	object = upl->map_object;

	if (upl->flags & UPL_SHADOWED) {
	        vm_object_lock(object);
		shadow_object = object->shadow;
	} else
		shadow_object = object;

	entry = offset/PAGE_SIZE;
	target_offset = (vm_object_offset_t)offset;

	assert(!(target_offset & PAGE_MASK));
	assert(!(xfer_size & PAGE_MASK));

	if (upl->flags & UPL_KERNEL_OBJECT)
		vm_object_lock_shared(shadow_object);
	else
		vm_object_lock(shadow_object);

	if (upl->flags & UPL_ACCESS_BLOCKED) {
		assert(shadow_object->blocked_access);
		shadow_object->blocked_access = FALSE;
		vm_object_wakeup(object, VM_OBJECT_EVENT_UNBLOCKED);
	}

	dwp = &dw_array[0];
	dw_count = 0;
	dw_limit = DELAYED_WORK_LIMIT(DEFAULT_DELAYED_WORK_LIMIT);

	if ((error & UPL_ABORT_DUMP_PAGES) && (upl->flags & UPL_KERNEL_OBJECT))
		panic("upl_abort_range: kernel_object being DUMPED");

	while (xfer_size) {
		vm_page_t	t, m;
		unsigned int	pg_num;
		boolean_t	needed;

		pg_num = (unsigned int) (target_offset/PAGE_SIZE);
		assert(pg_num == target_offset/PAGE_SIZE);

		needed = FALSE;

		if (user_page_list)
			needed = user_page_list[pg_num].needed;

		dwp->dw_mask = 0;
		m = VM_PAGE_NULL;

		if (upl->flags & UPL_LITE) {

			if (lite_list[pg_num>>5] & (1 << (pg_num & 31))) {
				lite_list[pg_num>>5] &= ~(1 << (pg_num & 31));

				if ( !(upl->flags & UPL_KERNEL_OBJECT))
					m = vm_page_lookup(shadow_object, target_offset +
							   (upl->offset - shadow_object->paging_offset));
			}
		}
		if (upl->flags & UPL_SHADOWED) {
		        if ((t = vm_page_lookup(object, target_offset))	!= VM_PAGE_NULL) {
			        t->vmp_free_when_done = FALSE;

				VM_PAGE_FREE(t);

				if (m == VM_PAGE_NULL)
					m = vm_page_lookup(shadow_object, target_offset + object->vo_shadow_offset);
			}
		}
		if ((upl->flags & UPL_KERNEL_OBJECT))
			goto abort_next_page;

		if (m != VM_PAGE_NULL) {

			assert(m->vmp_q_state != VM_PAGE_USED_BY_COMPRESSOR);

			if (m->vmp_absent) {
			        boolean_t must_free = TRUE;

				/*
				 * COPYOUT = FALSE case
				 * check for error conditions which must
				 * be passed back to the pages customer
				 */
				if (error & UPL_ABORT_RESTART) {
					m->vmp_restart = TRUE;
					m->vmp_absent = FALSE;
					m->vmp_unusual = TRUE;
					must_free = FALSE;
				} else if (error & UPL_ABORT_UNAVAILABLE) {
					m->vmp_restart = FALSE;
					m->vmp_unusual = TRUE;
					must_free = FALSE;
				} else if (error & UPL_ABORT_ERROR) {
					m->vmp_restart = FALSE;
					m->vmp_absent = FALSE;
					m->vmp_error = TRUE;
					m->vmp_unusual = TRUE;
					must_free = FALSE;
				}
				if (m->vmp_clustered && needed == FALSE) {
					/*
					 * This page was a part of a speculative
					 * read-ahead initiated by the kernel
					 * itself.  No one is expecting this
					 * page and no one will clean up its
					 * error state if it ever becomes valid
					 * in the future.
					 * We have to free it here.
					 */
					must_free = TRUE;
				}
				m->vmp_cleaning = FALSE;

				if (m->vmp_overwriting && !m->vmp_busy) {
					/*
					 * this shouldn't happen since
					 * this is an 'absent' page, but
					 * it doesn't hurt to check for
					 * the 'alternate' method of
					 * stabilizing the page...
					 * we will mark 'busy' to be cleared
					 * in the following code which will
					 * take care of the primary stabilzation
					 * method (i.e. setting 'busy' to TRUE)
					 */
					dwp->dw_mask |= DW_vm_page_unwire;
				}
				m->vmp_overwriting = FALSE;

				dwp->dw_mask |= (DW_clear_busy | DW_PAGE_WAKEUP);

				if (must_free == TRUE)
					dwp->dw_mask |= DW_vm_page_free;
				else
					dwp->dw_mask |= DW_vm_page_activate;
			} else {
			        /*
				 * Handle the trusted pager throttle.
				 */
			        if (m->vmp_laundry)
					dwp->dw_mask |= DW_vm_pageout_throttle_up;

				if (upl->flags & UPL_ACCESS_BLOCKED) {
					/*
					 * We blocked access to the pages in this UPL.
					 * Clear the "busy" bit and wake up any waiter
					 * for this page.
					 */
					dwp->dw_mask |= DW_clear_busy;
				}
				if (m->vmp_overwriting) {
					if (m->vmp_busy)
						dwp->dw_mask |= DW_clear_busy;
					else {
						/*
						 * deal with the 'alternate' method
						 * of stabilizing the page...
						 * we will either free the page
						 * or mark 'busy' to be cleared
						 * in the following code which will
						 * take care of the primary stabilzation
						 * method (i.e. setting 'busy' to TRUE)
						 */
						dwp->dw_mask |= DW_vm_page_unwire;
					}
					m->vmp_overwriting = FALSE;
				}
				m->vmp_free_when_done = FALSE;
				m->vmp_cleaning = FALSE;

				if (error & UPL_ABORT_DUMP_PAGES) {
					pmap_disconnect(VM_PAGE_GET_PHYS_PAGE(m));

					dwp->dw_mask |= DW_vm_page_free;
				} else {
					if (!(dwp->dw_mask & DW_vm_page_unwire)) {
						if (error & UPL_ABORT_REFERENCE) {
							/*
							 * we've been told to explictly
							 * reference this page... for
							 * file I/O, this is done by
							 * implementing an LRU on the inactive q
							 */
							dwp->dw_mask |= DW_vm_page_lru;

						} else if ( !VM_PAGE_PAGEABLE(m))
							dwp->dw_mask |= DW_vm_page_deactivate_internal;
					}
					dwp->dw_mask |= DW_PAGE_WAKEUP;
				}
			}
		}
abort_next_page:
		target_offset += PAGE_SIZE_64;
		xfer_size -= PAGE_SIZE;
		entry++;

		if (dwp->dw_mask) {
			if (dwp->dw_mask & ~(DW_clear_busy | DW_PAGE_WAKEUP)) {
				VM_PAGE_ADD_DELAYED_WORK(dwp, m, dw_count);

				if (dw_count >= dw_limit) {
					vm_page_do_delayed_work(shadow_object, VM_KERN_MEMORY_NONE, &dw_array[0], dw_count);

					dwp = &dw_array[0];
					dw_count = 0;
				}
			} else {
				if (dwp->dw_mask & DW_clear_busy)
					m->vmp_busy = FALSE;

				if (dwp->dw_mask & DW_PAGE_WAKEUP)
					PAGE_WAKEUP(m);
			}
		}
	}
	if (dw_count)
		vm_page_do_delayed_work(shadow_object, VM_KERN_MEMORY_NONE, &dw_array[0], dw_count);

	occupied = 1;

	if (upl->flags & UPL_DEVICE_MEMORY)  {
		occupied = 0;
	} else if (upl->flags & UPL_LITE) {
		int	pg_num;
		int	i;

		pg_num = upl->size/PAGE_SIZE;
		pg_num = (pg_num + 31) >> 5;
		occupied = 0;

		for (i = 0; i < pg_num; i++) {
			if (lite_list[i] != 0) {
				occupied = 1;
				break;
			}
		}
	} else {
		if (vm_page_queue_empty(&upl->map_object->memq))
			occupied = 0;
	}
	if (occupied == 0) {
		/*
		 * If this UPL element belongs to a Vector UPL and is
		 * empty, then this is the right function to deallocate
		 * it. So go ahead set the *empty variable. The flag
		 * UPL_COMMIT_NOTIFY_EMPTY, from the caller's point of view
		 * should be considered relevant for the Vector UPL and
		 * not the internal UPLs.
		 */
		if ((upl->flags & UPL_COMMIT_NOTIFY_EMPTY) || isVectorUPL)
			*empty = TRUE;

		if (object == shadow_object && !(upl->flags & UPL_KERNEL_OBJECT)) {
		        /*
			 * this is not a paging object
			 * so we need to drop the paging reference
			 * that was taken when we created the UPL
			 * against this object
			 */
			vm_object_activity_end(shadow_object);
			vm_object_collapse(shadow_object, 0, TRUE);
		} else {
		         /*
			  * we dontated the paging reference to
			  * the map object... vm_pageout_object_terminate
			  * will drop this reference
			  */
		}
	}
	vm_object_unlock(shadow_object);
	if (object != shadow_object)
	        vm_object_unlock(object);

	if(!isVectorUPL)
		upl_unlock(upl);
	else {
		/*
		* If we completed our operations on an UPL that is
	 	* part of a Vectored UPL and if empty is TRUE, then
	 	* we should go ahead and deallocate this UPL element.
	 	* Then we check if this was the last of the UPL elements
	 	* within that Vectored UPL. If so, set empty to TRUE
	 	* so that in ubc_upl_abort_range or ubc_upl_abort, we
	 	* can go ahead and deallocate the Vector UPL too.
	 	*/
		if(*empty == TRUE) {
			*empty = vector_upl_set_subupl(vector_upl, upl,0);
			upl_deallocate(upl);
		}
		goto process_upl_to_abort;
	}

	return KERN_SUCCESS;
}