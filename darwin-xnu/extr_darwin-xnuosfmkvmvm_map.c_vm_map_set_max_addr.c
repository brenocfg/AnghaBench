#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;

/* Variables and functions */

void
vm_map_set_max_addr(vm_map_t map, vm_map_offset_t new_max_offset)
{
#if defined(__arm64__)
	vm_map_offset_t max_supported_offset = 0;
	vm_map_offset_t old_max_offset = map->max_offset;
	max_supported_offset = pmap_max_offset(vm_map_is_64bit(map), ARM_PMAP_MAX_OFFSET_JUMBO);

	new_max_offset = trunc_page(new_max_offset);

	/* The address space cannot be shrunk using this routine. */
	if (old_max_offset >= new_max_offset) {
		return;
	}

	if (max_supported_offset < new_max_offset) {
		new_max_offset = max_supported_offset;
	}

	map->max_offset = new_max_offset;

	if (map->holes_list->prev->vme_end == old_max_offset) {
		/*
		 * There is already a hole at the end of the map; simply make it bigger.
		 */
		map->holes_list->prev->vme_end = map->max_offset;
	} else {
		/*
		 * There is no hole at the end, so we need to create a new hole
		 * for the new empty space we're creating.
		 */
		struct vm_map_links *new_hole = zalloc(vm_map_holes_zone);
		new_hole->start = old_max_offset;
		new_hole->end = map->max_offset;
		new_hole->prev = map->holes_list->prev;
		new_hole->next = (struct vm_map_entry *)map->holes_list;
		map->holes_list->prev->links.next = (struct vm_map_entry *)new_hole;
		map->holes_list->prev = (struct vm_map_entry *)new_hole;
	}
#else
	(void)map;
	(void)new_max_offset;
#endif
}