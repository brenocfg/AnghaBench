#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ vme_end; scalar_t__ vme_start; struct TYPE_5__* vme_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 scalar_t__ vm_map_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
vm_map_range_check(
	vm_map_t		map,
	vm_map_offset_t		start,
	vm_map_offset_t		end,
	vm_map_entry_t		*entry)
{
	vm_map_entry_t		cur;
	vm_map_offset_t		prev;

	/*
	 * 	Basic sanity checks first
	 */
	if (start < vm_map_min(map) || end > vm_map_max(map) || start > end)
		return (FALSE);

	/*
	 * 	Check first if the region starts within a valid
	 *	mapping for the map.
	 */
	if (!vm_map_lookup_entry(map, start, &cur))
		return (FALSE);

	/*
	 *	Optimize for the case that the region is contained
	 *	in a single map entry.
	 */
	if (entry != (vm_map_entry_t *) NULL)
		*entry = cur;
	if (end <= cur->vme_end)
		return (TRUE);

	/*
	 * 	If the region is not wholly contained within a
	 * 	single entry, walk the entries looking for holes.
	 */
	prev = cur->vme_end;
	cur = cur->vme_next;
	while ((cur != vm_map_to_entry(map)) && (prev == cur->vme_start)) {
		if (end <= cur->vme_end)
			return (TRUE);
		prev = cur->vme_end;
		cur = cur->vme_next;
	}
	return (FALSE);
}