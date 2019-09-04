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
typedef  scalar_t__ vm_inherit_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ vme_start; struct TYPE_6__* vme_next; scalar_t__ inheritance; int /*<<< orphan*/  use_pmap; scalar_t__ is_sub_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VM_INHERIT_COPY ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vm_map_clip_end (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 
 TYPE_1__* vm_map_to_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_inherit(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end,
	vm_inherit_t	new_inheritance)
{
	vm_map_entry_t	entry;
	vm_map_entry_t	temp_entry;

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &temp_entry)) {
		entry = temp_entry;
	}
	else {
		temp_entry = temp_entry->vme_next;
		entry = temp_entry;
	}

	/* first check entire range for submaps which can't support the */
	/* given inheritance. */
	while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
		if(entry->is_sub_map) {
			if(new_inheritance == VM_INHERIT_COPY) {
				vm_map_unlock(map);
				return(KERN_INVALID_ARGUMENT);
			}
		}

		entry = entry->vme_next;
	}

	entry = temp_entry;
	if (entry != vm_map_to_entry(map)) {
		/* clip and unnest if necessary */
		vm_map_clip_start(map, entry, start);
	}

	while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
		vm_map_clip_end(map, entry, end);
		if (entry->is_sub_map) {
			/* clip did unnest if needed */
			assert(!entry->use_pmap);
		}

		entry->inheritance = new_inheritance;

		entry = entry->vme_next;
	}

	vm_map_unlock(map);
	return(KERN_SUCCESS);
}