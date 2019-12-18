#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  unsigned int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {scalar_t__ purgable; scalar_t__ copy; scalar_t__ copy_strategy; scalar_t__ resident_page_count; scalar_t__ wired_page_count; scalar_t__ activity_in_progress; scalar_t__ paging_in_progress; int /*<<< orphan*/ * pager; } ;
typedef  int /*<<< orphan*/  SInt32 ;

/* Variables and functions */
 int C_DONT_BLOCK ; 
 int /*<<< orphan*/  DBG_MACH_VM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MEMORY_OBJECT_COPY_NONE ; 
 int /*<<< orphan*/  OBJECT_PURGE_ONE ; 
 int /*<<< orphan*/  OSAddAtomic (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REAP_PURGEABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_1__*) ; 
 scalar_t__ VM_OBJECT_NULL ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 scalar_t__ VM_PURGABLE_EMPTY ; 
 scalar_t__ VM_PURGABLE_VOLATILE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_compressor_pager_count (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 unsigned int vm_compressor_pager_get_count (int /*<<< orphan*/ *) ; 
 unsigned int vm_compressor_pager_reap_pages (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_owner_compressed_update (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  vm_object_reap_pages (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int vm_page_purgeable_count ; 
 scalar_t__ vm_page_purgeable_wired_count ; 

uint64_t
vm_object_purge(vm_object_t object, int flags)
{
	unsigned int	object_page_count = 0, pgcount = 0;
	uint64_t	total_purged_pgcount = 0;
	boolean_t	skipped_object = FALSE;

        vm_object_lock_assert_exclusive(object);

	if (object->purgable == VM_PURGABLE_DENY)
		return 0;

	assert(object->copy == VM_OBJECT_NULL);
	assert(object->copy_strategy == MEMORY_OBJECT_COPY_NONE);

	/*
	 * We need to set the object's state to VM_PURGABLE_EMPTY *before*
	 * reaping its pages.  We update vm_page_purgeable_count in bulk
	 * and we don't want vm_page_remove() to update it again for each
	 * page we reap later.
	 *
	 * For the purgeable ledgers, pages from VOLATILE and EMPTY objects
	 * are all accounted for in the "volatile" ledgers, so this does not
	 * make any difference.
	 * If we transitioned directly from NONVOLATILE to EMPTY,
	 * vm_page_purgeable_count must have been updated when the object
	 * was dequeued from its volatile queue and the purgeable ledgers
	 * must have also been updated accordingly at that time (in
	 * vm_object_purgable_control()).
	 */
	if (object->purgable == VM_PURGABLE_VOLATILE) {
		unsigned int delta;
		assert(object->resident_page_count >=
		       object->wired_page_count);
		delta = (object->resident_page_count -
			 object->wired_page_count);
		if (delta != 0) {
			assert(vm_page_purgeable_count >=
			       delta);
			OSAddAtomic(-delta,
				    (SInt32 *)&vm_page_purgeable_count);
		}
		if (object->wired_page_count != 0) {
			assert(vm_page_purgeable_wired_count >=
			       object->wired_page_count);
			OSAddAtomic(-object->wired_page_count,
				    (SInt32 *)&vm_page_purgeable_wired_count);
		}
		object->purgable = VM_PURGABLE_EMPTY;
	}
	assert(object->purgable == VM_PURGABLE_EMPTY);
	
	object_page_count = object->resident_page_count;

	vm_object_reap_pages(object, REAP_PURGEABLE);

	if (object->resident_page_count >= object_page_count) {
		total_purged_pgcount = 0;
	} else {
		total_purged_pgcount = object_page_count - object->resident_page_count;
	}

	if (object->pager != NULL) {

		assert(VM_CONFIG_COMPRESSOR_IS_PRESENT);

		if (object->activity_in_progress == 0 &&
		    object->paging_in_progress == 0) {
			/*
			 * Also reap any memory coming from this object
			 * in the VM compressor.
			 *
			 * There are no operations in progress on the VM object
			 * and no operation can start while we're holding the
			 * VM object lock, so it's safe to reap the compressed
			 * pages and update the page counts.
			 */
			pgcount = vm_compressor_pager_get_count(object->pager);
			if (pgcount) {
				pgcount = vm_compressor_pager_reap_pages(object->pager, flags);
				vm_compressor_pager_count(object->pager,
							  -pgcount,
							  FALSE, /* shared */
							  object);
				vm_object_owner_compressed_update(object,
								  -pgcount);
			}
			if ( !(flags & C_DONT_BLOCK)) {
				assert(vm_compressor_pager_get_count(object->pager)
				       == 0);
			}
		} else {
			/*
			 * There's some kind of paging activity in progress
			 * for this object, which could result in a page
			 * being compressed or decompressed, possibly while
			 * the VM object is not locked, so it could race
			 * with us.
			 *
			 * We can't really synchronize this without possibly 
			 * causing a deadlock when the compressor needs to
			 * allocate or free memory while compressing or
			 * decompressing a page from a purgeable object
			 * mapped in the kernel_map...
			 *
			 * So let's not attempt to purge the compressor
			 * pager if there's any kind of operation in
			 * progress on the VM object.
			 */
			skipped_object = TRUE;
		}
	}

	vm_object_lock_assert_exclusive(object);

	total_purged_pgcount += pgcount;

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, (MACHDBG_CODE(DBG_MACH_VM, OBJECT_PURGE_ONE)),
			      VM_KERNEL_UNSLIDE_OR_PERM(object), /* purged object */
			      object_page_count,
			      total_purged_pgcount,
			      skipped_object,
			      0);

	return total_purged_pgcount;
}