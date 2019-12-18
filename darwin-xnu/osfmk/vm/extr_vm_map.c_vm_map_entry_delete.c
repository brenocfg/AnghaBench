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
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_16__ {scalar_t__ map_aligned; scalar_t__ wired_count; scalar_t__ user_wired_count; scalar_t__ is_sub_map; int /*<<< orphan*/  permanent; scalar_t__ vme_end; scalar_t__ vme_start; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * VME_OBJECT (TYPE_2__*) ; 
 TYPE_1__* VME_SUBMAP (TYPE_2__*) ; 
 int VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int page_aligned (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_deallocate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_entry_dispose (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_store_entry_unlink (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_map_entry_delete(
	vm_map_t	map,
	vm_map_entry_t	entry)
{
	vm_map_offset_t	s, e;
	vm_object_t	object;
	vm_map_t	submap;

	s = entry->vme_start;
	e = entry->vme_end;
	assert(page_aligned(s));
	assert(page_aligned(e));
	if (entry->map_aligned == TRUE) {
		assert(VM_MAP_PAGE_ALIGNED(s, VM_MAP_PAGE_MASK(map)));
		assert(VM_MAP_PAGE_ALIGNED(e, VM_MAP_PAGE_MASK(map)));
	}
	assert(entry->wired_count == 0);
	assert(entry->user_wired_count == 0);
	assert(!entry->permanent);

	if (entry->is_sub_map) {
		object = NULL;
		submap = VME_SUBMAP(entry);
	} else {
		submap = NULL;
		object = VME_OBJECT(entry);
	}

	vm_map_store_entry_unlink(map, entry);
	map->size -= e - s;

	vm_map_entry_dispose(map, entry);

	vm_map_unlock(map);
	/*
	 *	Deallocate the object only after removing all
	 *	pmap entries pointing to its pages.
	 */
	if (submap)
		vm_map_deallocate(submap);
	else
		vm_object_deallocate(object);

}