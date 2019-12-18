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
struct TYPE_6__ {scalar_t__ vme_start; struct TYPE_6__* vme_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_first_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_simplify_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_map_simplify_range(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end)
{
	vm_map_entry_t	entry;

	/*
	 * The map should be locked (for "write") by the caller.
	 */

	if (start >= end) {
		/* invalid address range */
		return;
	}

	start = vm_map_trunc_page(start,
				  VM_MAP_PAGE_MASK(map));
	end = vm_map_round_page(end,
				VM_MAP_PAGE_MASK(map));

	if (!vm_map_lookup_entry(map, start, &entry)) {
		/* "start" is not mapped and "entry" ends before "start" */
		if (entry == vm_map_to_entry(map)) {
			/* start with first entry in the map */
			entry = vm_map_first_entry(map);
		} else {
			/* start with next entry */
			entry = entry->vme_next;
		}
	}

	while (entry != vm_map_to_entry(map) &&
	       entry->vme_start <= end) {
		/* try and coalesce "entry" with its previous entry */
		vm_map_simplify_entry(map, entry);
		entry = entry->vme_next;
	}
}