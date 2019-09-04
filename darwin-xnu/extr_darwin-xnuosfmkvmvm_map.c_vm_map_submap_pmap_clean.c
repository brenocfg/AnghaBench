#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  addr64_t ;
struct TYPE_16__ {scalar_t__ vme_end; scalar_t__ vme_start; struct TYPE_16__* vme_next; scalar_t__ is_sub_map; } ;
struct TYPE_15__ {int /*<<< orphan*/  pmap; scalar_t__ map_refcnt; scalar_t__ mapped_in_other_pmaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_NULL ; 
 int /*<<< orphan*/  PMAP_OPTIONS_REMOVE ; 
 int /*<<< orphan*/ * VME_OBJECT (TYPE_2__*) ; 
 scalar_t__ VME_OFFSET (TYPE_2__*) ; 
 TYPE_1__* VME_SUBMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_1__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_1__*,scalar_t__,TYPE_2__**) ; 
 TYPE_2__* vm_map_to_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_pmap_protect_options (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_map_submap_pmap_clean(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end,
	vm_map_t	sub_map,
	vm_map_offset_t	offset)
{
	vm_map_offset_t	submap_start;
	vm_map_offset_t	submap_end;
	vm_map_size_t	remove_size;
	vm_map_entry_t	entry;

	submap_end = offset + (end - start);
	submap_start = offset;

	vm_map_lock_read(sub_map);
	if(vm_map_lookup_entry(sub_map, offset, &entry)) {

		remove_size = (entry->vme_end - entry->vme_start);
		if(offset > entry->vme_start)
			remove_size -= offset - entry->vme_start;


		if(submap_end < entry->vme_end) {
			remove_size -=
				entry->vme_end - submap_end;
		}
		if(entry->is_sub_map) {
			vm_map_submap_pmap_clean(
				sub_map,
				start,
				start + remove_size,
				VME_SUBMAP(entry),
				VME_OFFSET(entry));
		} else {

			if((map->mapped_in_other_pmaps) && (map->map_refcnt)
			   && (VME_OBJECT(entry) != NULL)) {
				vm_object_pmap_protect_options(
					VME_OBJECT(entry),
					(VME_OFFSET(entry) +
					 offset -
					 entry->vme_start),
					remove_size,
					PMAP_NULL,
					entry->vme_start,
					VM_PROT_NONE,
					PMAP_OPTIONS_REMOVE);
			} else {
				pmap_remove(map->pmap,
					    (addr64_t)start,
					    (addr64_t)(start + remove_size));
			}
		}
	}

	entry = entry->vme_next;

	while((entry != vm_map_to_entry(sub_map))
	      && (entry->vme_start < submap_end)) {
		remove_size = (entry->vme_end - entry->vme_start);
		if(submap_end < entry->vme_end) {
			remove_size -= entry->vme_end - submap_end;
		}
		if(entry->is_sub_map) {
			vm_map_submap_pmap_clean(
				sub_map,
				(start + entry->vme_start) - offset,
				((start + entry->vme_start) - offset) + remove_size,
				VME_SUBMAP(entry),
				VME_OFFSET(entry));
		} else {
			if((map->mapped_in_other_pmaps) && (map->map_refcnt)
			   && (VME_OBJECT(entry) != NULL)) {
				vm_object_pmap_protect_options(
					VME_OBJECT(entry),
					VME_OFFSET(entry),
					remove_size,
					PMAP_NULL,
					entry->vme_start,
					VM_PROT_NONE,
					PMAP_OPTIONS_REMOVE);
			} else {
				pmap_remove(map->pmap,
					    (addr64_t)((start + entry->vme_start)
						       - offset),
					    (addr64_t)(((start + entry->vme_start)
							- offset) + remove_size));
			}
		}
		entry = entry->vme_next;
	}
	vm_map_unlock_read(sub_map);
	return;
}