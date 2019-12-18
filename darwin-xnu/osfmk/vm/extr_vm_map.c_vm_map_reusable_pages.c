#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_25__ {int /*<<< orphan*/  reusable_pages_success; int /*<<< orphan*/  reusable_pages_shared; int /*<<< orphan*/  reusable_shared; int /*<<< orphan*/  reusable_pages_failure; int /*<<< orphan*/  reusable_nonwritable; } ;
struct TYPE_24__ {scalar_t__ vme_start; int protection; int /*<<< orphan*/  use_pmap; int /*<<< orphan*/  is_sub_map; scalar_t__ iokit_acct; int /*<<< orphan*/  vme_end; int /*<<< orphan*/  used_for_jit; struct TYPE_24__* vme_next; } ;
struct TYPE_23__ {scalar_t__ pmap; } ;
struct TYPE_22__ {int ref_count; scalar_t__ copy_strategy; struct TYPE_22__* shadow; struct TYPE_22__* copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_PROTECTION_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MEMORY_OBJECT_COPY_SYMMETRIC ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VME_ALIAS (TYPE_3__*) ; 
 int /*<<< orphan*/  VME_ALIAS_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VME_OBJECT (TYPE_3__*) ; 
 scalar_t__ VME_OFFSET (TYPE_3__*) ; 
 scalar_t__ VM_MEMORY_MALLOC_LARGE ; 
 int /*<<< orphan*/  VM_MEMORY_MALLOC_LARGE_REUSABLE ; 
 scalar_t__ VM_MEMORY_MALLOC_LARGE_REUSED ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  vm_map_entry_is_reusable (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_range_check (TYPE_2__*,scalar_t__,scalar_t__,TYPE_3__**) ; 
 TYPE_3__* vm_map_to_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_deactivate_pages (TYPE_1__*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 TYPE_4__ vm_page_stats_reusable ; 

__attribute__((used)) static kern_return_t
vm_map_reusable_pages(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end)
{
	vm_map_entry_t 			entry;
	vm_object_t			object;
	vm_object_offset_t		start_offset, end_offset;
	vm_map_offset_t			pmap_offset;

	/*
	 * The MADV_REUSABLE operation doesn't require any changes to the
	 * vm_map_entry_t's, so the read lock is sufficient.
	 */

	vm_map_lock_read(map);
	assert(map->pmap != kernel_pmap);	/* protect alias access */

	/*
	 * The madvise semantics require that the address range be fully
	 * allocated with no holes.  Otherwise, we're required to return
	 * an error.
	 */

	if (!vm_map_range_check(map, start, end, &entry)) {
		vm_map_unlock_read(map);
		vm_page_stats_reusable.reusable_pages_failure++;
		return KERN_INVALID_ADDRESS;
	}

	/*
	 * Examine each vm_map_entry_t in the range.
	 */
	for (; entry != vm_map_to_entry(map) && entry->vme_start < end;
	     entry = entry->vme_next) {
		int kill_pages = 0;

		/*
		 * Sanity check on the VM map entry.
		 */
		if (! vm_map_entry_is_reusable(entry)) {
			vm_map_unlock_read(map);
			vm_page_stats_reusable.reusable_pages_failure++;
			return KERN_INVALID_ADDRESS;
		}

		if (! (entry->protection & VM_PROT_WRITE) && !entry->used_for_jit) {
			/* not writable: can't discard contents */
			vm_map_unlock_read(map);
			vm_page_stats_reusable.reusable_nonwritable++;
			vm_page_stats_reusable.reusable_pages_failure++;
			return KERN_PROTECTION_FAILURE;
		}

		/*
		 * The first time through, the start address could be anywhere
		 * within the vm_map_entry we found.  So adjust the offset to
		 * correspond.
		 */
		if (entry->vme_start < start) {
			start_offset = start - entry->vme_start;
			pmap_offset = start;
		} else {
			start_offset = 0;
			pmap_offset = entry->vme_start;
		}
		end_offset = MIN(end, entry->vme_end) - entry->vme_start;
		start_offset += VME_OFFSET(entry);
		end_offset += VME_OFFSET(entry);

		assert(!entry->is_sub_map);
		object = VME_OBJECT(entry);
		if (object == VM_OBJECT_NULL)
			continue;


		vm_object_lock(object);
		if (((object->ref_count == 1) ||
		     (object->copy_strategy != MEMORY_OBJECT_COPY_SYMMETRIC &&
		      object->copy == VM_OBJECT_NULL)) &&
		    object->shadow == VM_OBJECT_NULL &&
		    /*
		     * "iokit_acct" entries are billed for their virtual size
		     * (rather than for their resident pages only), so they
		     * wouldn't benefit from making pages reusable, and it
		     * would be hard to keep track of pages that are both
		     * "iokit_acct" and "reusable" in the pmap stats and
		     * ledgers.
		     */
		    !(entry->iokit_acct ||
		      (!entry->is_sub_map && !entry->use_pmap))) {
			if (object->ref_count != 1) {
				vm_page_stats_reusable.reusable_shared++;
			}
			kill_pages = 1;
		} else {
			kill_pages = -1;
		}
		if (kill_pages != -1) {
			vm_object_deactivate_pages(object,
						   start_offset,
						   end_offset - start_offset,
						   kill_pages,
						   TRUE /*reusable_pages*/,
						   map->pmap,
						   pmap_offset);
		} else {
			vm_page_stats_reusable.reusable_pages_shared++;
		}
		vm_object_unlock(object);

		if (VME_ALIAS(entry) == VM_MEMORY_MALLOC_LARGE ||
		    VME_ALIAS(entry) == VM_MEMORY_MALLOC_LARGE_REUSED) {
			/*
			 * XXX
			 * We do not hold the VM map exclusively here.
			 * The "alias" field is not that critical, so it's
			 * safe to update it here, as long as it is the only
			 * one that can be modified while holding the VM map
			 * "shared".
			 */
			VME_ALIAS_SET(entry, VM_MEMORY_MALLOC_LARGE_REUSABLE);
		}
	}

	vm_map_unlock_read(map);
	vm_page_stats_reusable.reusable_pages_success++;
	return KERN_SUCCESS;
}