#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int vm_behavior_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ vme_start; int behavior; struct TYPE_6__* vme_next; int /*<<< orphan*/  zero_wired_pages; int /*<<< orphan*/  use_pmap; int /*<<< orphan*/  is_sub_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
#define  VM_BEHAVIOR_CAN_REUSE 139 
#define  VM_BEHAVIOR_DEFAULT 138 
#define  VM_BEHAVIOR_DONTNEED 137 
#define  VM_BEHAVIOR_FREE 136 
#define  VM_BEHAVIOR_PAGEOUT 135 
#define  VM_BEHAVIOR_RANDOM 134 
#define  VM_BEHAVIOR_REUSABLE 133 
#define  VM_BEHAVIOR_REUSE 132 
#define  VM_BEHAVIOR_RSEQNTL 131 
#define  VM_BEHAVIOR_SEQUENTIAL 130 
#define  VM_BEHAVIOR_WILLNEED 129 
#define  VM_BEHAVIOR_ZERO_WIRED_PAGES 128 
 int VM_SYNC_CONTIGUOUS ; 
 int VM_SYNC_DEACTIVATE ; 
 int VM_SYNC_KILLPAGES ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_MAP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_map_can_reuse (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_end (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_msync (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_map_pageout (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_range_check (int /*<<< orphan*/ ,scalar_t__,scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  vm_map_reusable_pages (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_reuse_pages (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_willneed (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

kern_return_t
vm_map_behavior_set(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end,
	vm_behavior_t	new_behavior)
{
	vm_map_entry_t	entry;
	vm_map_entry_t	temp_entry;

	XPR(XPR_VM_MAP,
	    "vm_map_behavior_set, 0x%X start 0x%X end 0x%X behavior %d",
	    map, start, end, new_behavior, 0);

	if (start > end ||
	    start < vm_map_min(map) ||
	    end > vm_map_max(map)) {
		return KERN_NO_SPACE;
	}

	switch (new_behavior) {

	/*
	 * This first block of behaviors all set a persistent state on the specified
	 * memory range.  All we have to do here is to record the desired behavior
	 * in the vm_map_entry_t's.
	 */

	case VM_BEHAVIOR_DEFAULT:
	case VM_BEHAVIOR_RANDOM:
	case VM_BEHAVIOR_SEQUENTIAL:
	case VM_BEHAVIOR_RSEQNTL:
	case VM_BEHAVIOR_ZERO_WIRED_PAGES:
		vm_map_lock(map);

		/*
		 *	The entire address range must be valid for the map.
		 * 	Note that vm_map_range_check() does a
		 *	vm_map_lookup_entry() internally and returns the
		 *	entry containing the start of the address range if
		 *	the entire range is valid.
		 */
		if (vm_map_range_check(map, start, end, &temp_entry)) {
			entry = temp_entry;
			vm_map_clip_start(map, entry, start);
		}
		else {
			vm_map_unlock(map);
			return(KERN_INVALID_ADDRESS);
		}

		while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
			vm_map_clip_end(map, entry, end);
			if (entry->is_sub_map) {
				assert(!entry->use_pmap);
			}

			if( new_behavior == VM_BEHAVIOR_ZERO_WIRED_PAGES ) {
				entry->zero_wired_pages = TRUE;
			} else {
				entry->behavior = new_behavior;
			}
			entry = entry->vme_next;
		}

		vm_map_unlock(map);
		break;

	/*
	 * The rest of these are different from the above in that they cause
	 * an immediate action to take place as opposed to setting a behavior that
	 * affects future actions.
	 */

	case VM_BEHAVIOR_WILLNEED:
		return vm_map_willneed(map, start, end);

	case VM_BEHAVIOR_DONTNEED:
		return vm_map_msync(map, start, end - start, VM_SYNC_DEACTIVATE | VM_SYNC_CONTIGUOUS);

	case VM_BEHAVIOR_FREE:
		return vm_map_msync(map, start, end - start, VM_SYNC_KILLPAGES | VM_SYNC_CONTIGUOUS);

	case VM_BEHAVIOR_REUSABLE:
		return vm_map_reusable_pages(map, start, end);

	case VM_BEHAVIOR_REUSE:
		return vm_map_reuse_pages(map, start, end);

	case VM_BEHAVIOR_CAN_REUSE:
		return vm_map_can_reuse(map, start, end);

#if MACH_ASSERT
	case VM_BEHAVIOR_PAGEOUT:
		return vm_map_pageout(map, start, end);
#endif /* MACH_ASSERT */

	default:
		return(KERN_INVALID_ARGUMENT);
	}

	return(KERN_SUCCESS);
}