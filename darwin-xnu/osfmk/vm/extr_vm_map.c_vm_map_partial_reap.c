#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_20__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_25__ {int /*<<< orphan*/  vme_end; int /*<<< orphan*/  vme_start; int /*<<< orphan*/  is_sub_map; struct TYPE_25__* vme_next; } ;
struct TYPE_22__ {int /*<<< orphan*/  entries_pageable; } ;
struct TYPE_24__ {TYPE_1__ hdr; int /*<<< orphan*/  max_offset; int /*<<< orphan*/  min_offset; } ;
struct TYPE_23__ {scalar_t__ internal; int ref_count; int /*<<< orphan*/  pager; scalar_t__ resident_page_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PMAP_NULL ; 
 scalar_t__ TRUE ; 
 TYPE_20__* VME_OBJECT (TYPE_3__*) ; 
 TYPE_3__* VM_MAP_ENTRY_NULL ; 
 TYPE_2__* VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_SHIFT (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_NO_PMAP_CLEANUP ; 
 int /*<<< orphan*/  VM_MAP_REMOVE_SAVE_ENTRIES ; 
 scalar_t__ vm_compressor_pager_get_count (int /*<<< orphan*/ ) ; 
 TYPE_2__* vm_map_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_delete (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_destroy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_disable_hole_optimization (TYPE_2__*) ; 
 TYPE_3__* vm_map_first_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_set_page_shift (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_map_to_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 

kern_return_t vm_map_partial_reap(vm_map_t map, unsigned int *reclaimed_resident, unsigned int *reclaimed_compressed)
{
	vm_map_entry_t	entry = VM_MAP_ENTRY_NULL;
	vm_map_entry_t next_entry;
	kern_return_t	kr = KERN_SUCCESS;
	vm_map_t 	zap_map;

	vm_map_lock(map);

	/*
	 * We use a "zap_map" to avoid having to unlock
	 * the "map" in vm_map_delete().
	 */
	zap_map = vm_map_create(PMAP_NULL,
				map->min_offset,
				map->max_offset,
				map->hdr.entries_pageable);

	if (zap_map == VM_MAP_NULL) {
		return KERN_RESOURCE_SHORTAGE;
	}

	vm_map_set_page_shift(zap_map,
			      VM_MAP_PAGE_SHIFT(map));
	vm_map_disable_hole_optimization(zap_map);

	for (entry = vm_map_first_entry(map);
	     entry != vm_map_to_entry(map);
	     entry = next_entry) {
		next_entry = entry->vme_next;

		if (VME_OBJECT(entry) &&
		    !entry->is_sub_map &&
		    (VME_OBJECT(entry)->internal == TRUE) &&
		    (VME_OBJECT(entry)->ref_count == 1)) {

			*reclaimed_resident += VME_OBJECT(entry)->resident_page_count;
			*reclaimed_compressed += vm_compressor_pager_get_count(VME_OBJECT(entry)->pager);

			(void)vm_map_delete(map,
					    entry->vme_start,
					    entry->vme_end,
					    VM_MAP_REMOVE_SAVE_ENTRIES,
					    zap_map);
		}
	}

	vm_map_unlock(map);

        /*
	 * Get rid of the "zap_maps" and all the map entries that
         * they may still contain.
         */
        if (zap_map != VM_MAP_NULL) {
                vm_map_destroy(zap_map, VM_MAP_REMOVE_NO_PMAP_CLEANUP);
                zap_map = VM_MAP_NULL;
        }

	return kr;
}