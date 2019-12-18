#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
typedef  scalar_t__ memory_object_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_22__ {int /*<<< orphan*/  vm_compressor_failed; } ;
struct TYPE_21__ {scalar_t__ pager; scalar_t__ activity_in_progress; scalar_t__ purgable; int /*<<< orphan*/ * vo_owner; scalar_t__ vo_ledger_tag; scalar_t__ paging_offset; scalar_t__ pager_initialized; } ;
struct TYPE_20__ {scalar_t__ vmp_tabled; scalar_t__ vmp_offset; int /*<<< orphan*/  vmp_laundry; int /*<<< orphan*/  vmp_free_when_done; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ MEMORY_OBJECT_NULL ; 
 int /*<<< orphan*/  PAGE_WAKEUP_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_PAGEOUT_DEBUG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 TYPE_2__* VM_PAGE_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PAGE_WIRED (TYPE_1__*) ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 int /*<<< orphan*/  VM_STAT_INCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compressions ; 
 int /*<<< orphan*/  vm_compressor_pager_count (scalar_t__,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ vm_compressor_pager_put (scalar_t__,scalar_t__,int /*<<< orphan*/ ,void**,char*,int*) ; 
 int /*<<< orphan*/  vm_object_activity_end (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_collapse (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_compressor_pager_create (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_owner_compressed_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_remove (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 
 int /*<<< orphan*/  vm_pageout_dirty_no_pager ; 
 TYPE_3__ vm_pageout_vminfo ; 

kern_return_t
vm_pageout_compress_page(void **current_chead, char *scratch_buf, vm_page_t m)
{
	vm_object_t	object;
	memory_object_t	pager;
	int		compressed_count_delta;
	kern_return_t	retval;

	object = VM_PAGE_OBJECT(m);

	assert(!m->vmp_free_when_done);
	assert(!m->vmp_laundry);

	pager = object->pager;

	if (!object->pager_initialized || pager == MEMORY_OBJECT_NULL)  {

		KERNEL_DEBUG(0xe0400010 | DBG_FUNC_START, object, pager, 0, 0, 0);

		vm_object_lock(object);

		/*
		 * If there is no memory object for the page, create
		 * one and hand it to the compression pager.
		 */

		if (!object->pager_initialized)
			vm_object_collapse(object, (vm_object_offset_t) 0, TRUE);
		if (!object->pager_initialized)
			vm_object_compressor_pager_create(object);

		pager = object->pager;

		if (!object->pager_initialized || pager == MEMORY_OBJECT_NULL) {
			/*
			 * Still no pager for the object,
			 * or the pager has been destroyed.
			 * Reactivate the page.
			 *
			 * Should only happen if there is no
			 * compression pager
			 */
			PAGE_WAKEUP_DONE(m);

			vm_page_lockspin_queues();
			vm_page_activate(m);
			VM_PAGEOUT_DEBUG(vm_pageout_dirty_no_pager, 1);
			vm_page_unlock_queues();

			/*
			 *	And we are done with it.
			 */
			vm_object_activity_end(object);
			vm_object_unlock(object);

			return KERN_FAILURE;
		}
		vm_object_unlock(object);

		KERNEL_DEBUG(0xe0400010 | DBG_FUNC_END, object, pager, 0, 0, 0);
	}
	assert(object->pager_initialized && pager != MEMORY_OBJECT_NULL);
	assert(object->activity_in_progress > 0);

	retval = vm_compressor_pager_put(
		pager,
		m->vmp_offset + object->paging_offset,
		VM_PAGE_GET_PHYS_PAGE(m),
		current_chead,
		scratch_buf,
		&compressed_count_delta);

	vm_object_lock(object);

	assert(object->activity_in_progress > 0);
	assert(VM_PAGE_OBJECT(m) == object);
	assert( !VM_PAGE_WIRED(m));

	vm_compressor_pager_count(pager,
				  compressed_count_delta,
				  FALSE, /* shared_lock */
				  object);

	if (retval == KERN_SUCCESS) {
		/*
		 * If the object is purgeable, its owner's
		 * purgeable ledgers will be updated in
		 * vm_page_remove() but the page still
		 * contributes to the owner's memory footprint,
		 * so account for it as such.
		 */
		if ((object->purgable != VM_PURGABLE_DENY ||
		     object->vo_ledger_tag) &&
		    object->vo_owner != NULL) {
			/* one more compressed purgeable/tagged page */
			vm_object_owner_compressed_update(object,
							  +1);
		}
		VM_STAT_INCR(compressions);

		if (m->vmp_tabled)
			vm_page_remove(m, TRUE);

	} else {
		PAGE_WAKEUP_DONE(m);

		vm_page_lockspin_queues();

		vm_page_activate(m);
		vm_pageout_vminfo.vm_compressor_failed++;

		vm_page_unlock_queues();
	}
	vm_object_activity_end(object);
	vm_object_unlock(object);

	return retval;
}