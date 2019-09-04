#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {struct TYPE_11__* vme_next; int /*<<< orphan*/  vme_start; int /*<<< orphan*/  vme_end; } ;
struct TYPE_10__ {TYPE_2__* first_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 
 scalar_t__ vm_map_trunc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
first_free_is_valid_ll( vm_map_t map )
{
	vm_map_entry_t	entry, next;
	entry = vm_map_to_entry(map);
	next = entry->vme_next;
	while (vm_map_trunc_page(next->vme_start,
				 VM_MAP_PAGE_MASK(map)) ==
	       vm_map_trunc_page(entry->vme_end,
				 VM_MAP_PAGE_MASK(map)) ||
	       (vm_map_trunc_page(next->vme_start,
				  VM_MAP_PAGE_MASK(map)) ==
		vm_map_trunc_page(entry->vme_start,
				  VM_MAP_PAGE_MASK(map)) &&
		next != vm_map_to_entry(map))) {
		entry = next;
		next = entry->vme_next;
		if (entry == vm_map_to_entry(map))
			break;
	}
	if (map->first_free != entry) {
		printf("Bad first_free for map %p: %p should be %p\n",
		       map, map->first_free, entry);
		return FALSE;
	}
	return TRUE;
}