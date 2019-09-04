#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* vm_object_t ;
typedef  int vm_object_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int vm_map_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  scalar_t__ ppnum_t ;
struct TYPE_13__ {int vme_start; scalar_t__ is_sub_map; } ;
struct TYPE_12__ {int vo_shadow_offset; struct TYPE_12__* shadow; scalar_t__ phys_contiguous; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 scalar_t__ TRUE ; 
 TYPE_1__* VME_OBJECT (TYPE_2__*) ; 
 int VME_OFFSET (TYPE_2__*) ; 
 int /*<<< orphan*/  VME_SUBMAP (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 scalar_t__ VM_PAGE_GET_PHYS_PAGE (scalar_t__) ; 
 scalar_t__ VM_PAGE_NULL ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int /*<<< orphan*/  vm_fault (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int vm_map_trunc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 
 scalar_t__ vm_page_lookup (TYPE_1__*,int) ; 

ppnum_t
vm_map_get_phys_page(
	vm_map_t		map,
	vm_offset_t		addr)
{
	vm_object_offset_t	offset;
	vm_object_t		object;
	vm_map_offset_t 	map_offset;
	vm_map_entry_t		entry;
	ppnum_t			phys_page = 0;

	map_offset = vm_map_trunc_page(addr, PAGE_MASK);

	vm_map_lock(map);
	while (vm_map_lookup_entry(map, map_offset, &entry)) {

		if (VME_OBJECT(entry) == VM_OBJECT_NULL) {
			vm_map_unlock(map);
			return (ppnum_t) 0;
		}
		if (entry->is_sub_map) {
			vm_map_t	old_map;
			vm_map_lock(VME_SUBMAP(entry));
			old_map = map;
			map = VME_SUBMAP(entry);
			map_offset = (VME_OFFSET(entry) +
				      (map_offset - entry->vme_start));
			vm_map_unlock(old_map);
			continue;
		}
		if (VME_OBJECT(entry)->phys_contiguous) {
			/* These are  not standard pageable memory mappings */
			/* If they are not present in the object they will  */
			/* have to be picked up from the pager through the  */
			/* fault mechanism.  */
			if (VME_OBJECT(entry)->vo_shadow_offset == 0) {
				/* need to call vm_fault */
				vm_map_unlock(map);
				vm_fault(map, map_offset, VM_PROT_NONE, 
					FALSE /* change_wiring */, VM_KERN_MEMORY_NONE,
					THREAD_UNINT, NULL, 0);
				vm_map_lock(map);
				continue;
			}
			offset = (VME_OFFSET(entry) +
				  (map_offset - entry->vme_start));
			phys_page = (ppnum_t)
				((VME_OBJECT(entry)->vo_shadow_offset 
				  + offset) >> PAGE_SHIFT);
			break;
			
		}
		offset = (VME_OFFSET(entry) + (map_offset - entry->vme_start));
		object = VME_OBJECT(entry);
		vm_object_lock(object);
		while (TRUE) {
			vm_page_t dst_page = vm_page_lookup(object,offset);
	                if(dst_page == VM_PAGE_NULL) {
				if(object->shadow) {
					vm_object_t old_object;
					vm_object_lock(object->shadow);
					old_object = object;
					offset = offset + object->vo_shadow_offset;
					object = object->shadow;
					vm_object_unlock(old_object);
				} else {
					vm_object_unlock(object);
					break;
				}
			} else {
				phys_page = (ppnum_t)(VM_PAGE_GET_PHYS_PAGE(dst_page));
				vm_object_unlock(object);
				break;
			}
		}
		break;

	} 

	vm_map_unlock(map);
	return phys_page;
}