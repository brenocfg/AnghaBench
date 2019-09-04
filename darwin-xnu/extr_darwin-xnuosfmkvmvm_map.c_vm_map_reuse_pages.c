#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_18__ {int /*<<< orphan*/  reuse_pages_success; int /*<<< orphan*/  reuse_pages_failure; } ;
struct TYPE_17__ {scalar_t__ vme_start; int /*<<< orphan*/  is_sub_map; int /*<<< orphan*/  vme_end; struct TYPE_17__* vme_next; } ;
struct TYPE_16__ {scalar_t__ pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VME_ALIAS (TYPE_2__*) ; 
 int /*<<< orphan*/  VME_ALIAS_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VME_OBJECT (TYPE_2__*) ; 
 scalar_t__ VME_OFFSET (TYPE_2__*) ; 
 scalar_t__ VM_MEMORY_MALLOC_LARGE_REUSABLE ; 
 int /*<<< orphan*/  VM_MEMORY_MALLOC_LARGE_REUSED ; 
 scalar_t__ VM_OBJECT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  vm_map_entry_is_reusable (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_range_check (TYPE_1__*,scalar_t__,scalar_t__,TYPE_2__**) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_lock (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_reuse_pages (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_unlock (scalar_t__) ; 
 TYPE_3__ vm_page_stats_reusable ; 

__attribute__((used)) static kern_return_t
vm_map_reuse_pages(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end)
{
	vm_map_entry_t 			entry;
	vm_object_t			object;
	vm_object_offset_t		start_offset, end_offset;

	/*
	 * The MADV_REUSE operation doesn't require any changes to the
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
		vm_page_stats_reusable.reuse_pages_failure++;
		return KERN_INVALID_ADDRESS;
	}

	/*
	 * Examine each vm_map_entry_t in the range.
	 */
	for (; entry != vm_map_to_entry(map) && entry->vme_start < end;
	     entry = entry->vme_next) {
		/*
		 * Sanity check on the VM map entry.
		 */
		if (! vm_map_entry_is_reusable(entry)) {
			vm_map_unlock_read(map);
			vm_page_stats_reusable.reuse_pages_failure++;
			return KERN_INVALID_ADDRESS;
		}

		/*
		 * The first time through, the start address could be anywhere
		 * within the vm_map_entry we found.  So adjust the offset to
		 * correspond.
		 */
		if (entry->vme_start < start) {
			start_offset = start - entry->vme_start;
		} else {
			start_offset = 0;
		}
		end_offset = MIN(end, entry->vme_end) - entry->vme_start;
		start_offset += VME_OFFSET(entry);
		end_offset += VME_OFFSET(entry);

		assert(!entry->is_sub_map);
		object = VME_OBJECT(entry);
		if (object != VM_OBJECT_NULL) {
			vm_object_lock(object);
			vm_object_reuse_pages(object, start_offset, end_offset,
					      TRUE);
			vm_object_unlock(object);
		}

		if (VME_ALIAS(entry) == VM_MEMORY_MALLOC_LARGE_REUSABLE) {
			/*
			 * XXX
			 * We do not hold the VM map exclusively here.
			 * The "alias" field is not that critical, so it's
			 * safe to update it here, as long as it is the only
			 * one that can be modified while holding the VM map
			 * "shared".
			 */
			VME_ALIAS_SET(entry, VM_MEMORY_MALLOC_LARGE_REUSED);
		}
	}

	vm_map_unlock_read(map);
	vm_page_stats_reusable.reuse_pages_success++;
	return KERN_SUCCESS;
}