#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
struct vm_map_links {scalar_t__ end; struct vm_map_entry* next; struct vm_map_entry* prev; scalar_t__ start; } ;
struct TYPE_6__ {struct vm_map_entry* next; } ;
struct vm_map_entry {scalar_t__ vme_end; TYPE_1__ links; } ;
struct TYPE_8__ {scalar_t__ max_offset; TYPE_2__* holes_list; } ;
struct TYPE_7__ {struct vm_map_entry* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PMAP_MAX_OFFSET_JUMBO ; 
 scalar_t__ pmap_max_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_holes_zone ; 
 int /*<<< orphan*/  vm_map_is_64bit (TYPE_3__*) ; 
 struct vm_map_links* zalloc (int /*<<< orphan*/ ) ; 

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