#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_3__* vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  TYPE_4__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  vm_machine_attribute_val_t ;
typedef  scalar_t__ vm_machine_attribute_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_25__ {scalar_t__ vme_end; scalar_t__ vme_start; scalar_t__ is_sub_map; } ;
struct TYPE_24__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_23__ {scalar_t__ vo_shadow_offset; struct TYPE_23__* shadow; } ;
struct TYPE_22__ {int /*<<< orphan*/  vmp_fictitious; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MATTR_CACHE ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_2__* VME_OBJECT (TYPE_4__*) ; 
 scalar_t__ VME_OFFSET (TYPE_4__*) ; 
 TYPE_3__* VME_SUBMAP (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_attribute (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_attribute_cache_sync (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_3__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_3__*,scalar_t__,TYPE_4__**) ; 
 scalar_t__ vm_map_max (TYPE_3__*) ; 
 scalar_t__ vm_map_min (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_2__*) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 

kern_return_t
vm_map_machine_attribute(
	vm_map_t			map,
	vm_map_offset_t		start,
	vm_map_offset_t		end,
	vm_machine_attribute_t	attribute,
	vm_machine_attribute_val_t* value)		/* IN/OUT */
{
	kern_return_t	ret;
	vm_map_size_t sync_size;
	vm_map_entry_t entry;

	if (start < vm_map_min(map) || end > vm_map_max(map))
		return KERN_INVALID_ADDRESS;

	/* Figure how much memory we need to flush (in page increments) */
	sync_size = end - start;

	vm_map_lock(map);

	if (attribute != MATTR_CACHE) {
		/* If we don't have to find physical addresses, we */
		/* don't have to do an explicit traversal here.    */
		ret = pmap_attribute(map->pmap, start, end-start,
				     attribute, value);
		vm_map_unlock(map);
		return ret;
	}

	ret = KERN_SUCCESS;										/* Assume it all worked */

	while(sync_size) {
		if (vm_map_lookup_entry(map, start, &entry)) {
			vm_map_size_t	sub_size;
			if((entry->vme_end - start) > sync_size) {
				sub_size = sync_size;
				sync_size = 0;
			} else {
				sub_size = entry->vme_end - start;
				sync_size -= sub_size;
			}
			if(entry->is_sub_map) {
				vm_map_offset_t sub_start;
				vm_map_offset_t sub_end;

				sub_start = (start - entry->vme_start)
					+ VME_OFFSET(entry);
				sub_end = sub_start + sub_size;
				vm_map_machine_attribute(
					VME_SUBMAP(entry),
					sub_start,
					sub_end,
					attribute, value);
			} else {
				if (VME_OBJECT(entry)) {
					vm_page_t		m;
					vm_object_t		object;
					vm_object_t		base_object;
					vm_object_t		last_object;
					vm_object_offset_t	offset;
					vm_object_offset_t	base_offset;
					vm_map_size_t		range;
					range = sub_size;
					offset = (start - entry->vme_start)
						+ VME_OFFSET(entry);
					base_offset = offset;
					object = VME_OBJECT(entry);
					base_object = object;
					last_object = NULL;

					vm_object_lock(object);

					while (range) {
						m = vm_page_lookup(
							object, offset);

						if (m && !m->vmp_fictitious) {
						        ret =
								pmap_attribute_cache_sync(
									VM_PAGE_GET_PHYS_PAGE(m),
									PAGE_SIZE,
									attribute, value);

						} else if (object->shadow) {
						        offset = offset + object->vo_shadow_offset;
							last_object = object;
							object = object->shadow;
							vm_object_lock(last_object->shadow);
							vm_object_unlock(last_object);
							continue;
						}
						range -= PAGE_SIZE;

						if (base_object != object) {
						        vm_object_unlock(object);
							vm_object_lock(base_object);
							object = base_object;
						}
						/* Bump to the next page */
						base_offset += PAGE_SIZE;
						offset = base_offset;
					}
					vm_object_unlock(object);
				}
			}
			start += sub_size;
		} else {
			vm_map_unlock(map);
			return KERN_FAILURE;
		}

	}

	vm_map_unlock(map);

	return ret;
}