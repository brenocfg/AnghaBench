#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  int mach_vm_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_15__ {int protection; int vme_end; int vme_start; scalar_t__ is_sub_map; struct TYPE_15__* vme_next; } ;
struct TYPE_14__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_13__ {scalar_t__ purgable; int resident_page_count; scalar_t__ pager; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SIZE ; 
 TYPE_1__* VME_OBJECT (TYPE_3__*) ; 
 int VME_OFFSET (TYPE_3__*) ; 
 TYPE_1__* VM_OBJECT_NULL ; 
 int VM_PROT_WRITE ; 
 scalar_t__ VM_PURGABLE_EMPTY ; 
 scalar_t__ VM_PURGABLE_VOLATILE ; 
 int pmap_query_resident (int /*<<< orphan*/ ,int,int,int*) ; 
 scalar_t__ vm_compressor_pager_get_count (scalar_t__) ; 
 TYPE_3__* vm_map_first_entry (TYPE_2__*) ; 
 TYPE_3__* vm_map_to_entry (TYPE_2__*) ; 

kern_return_t
vm_map_query_volatile(
	vm_map_t	map,
	mach_vm_size_t	*volatile_virtual_size_p,
	mach_vm_size_t	*volatile_resident_size_p,
	mach_vm_size_t	*volatile_compressed_size_p,
	mach_vm_size_t	*volatile_pmap_size_p,
	mach_vm_size_t	*volatile_compressed_pmap_size_p)
{
	mach_vm_size_t	volatile_virtual_size;
	mach_vm_size_t	volatile_resident_count;
	mach_vm_size_t	volatile_compressed_count;
	mach_vm_size_t	volatile_pmap_count;
	mach_vm_size_t	volatile_compressed_pmap_count;
	mach_vm_size_t	resident_count;
	vm_map_entry_t	entry;
	vm_object_t	object;

	/* map should be locked by caller */

	volatile_virtual_size = 0;
	volatile_resident_count = 0;
	volatile_compressed_count = 0;
	volatile_pmap_count = 0;
	volatile_compressed_pmap_count = 0;

	for (entry = vm_map_first_entry(map);
	     entry != vm_map_to_entry(map);
	     entry = entry->vme_next) {
		mach_vm_size_t	pmap_resident_bytes, pmap_compressed_bytes;

		if (entry->is_sub_map) {
			continue;
		}
		if (! (entry->protection & VM_PROT_WRITE)) {
			continue;
		}
		object = VME_OBJECT(entry);
		if (object == VM_OBJECT_NULL) {
			continue;
		}
		if (object->purgable != VM_PURGABLE_VOLATILE &&
		    object->purgable != VM_PURGABLE_EMPTY) {
			continue;
		}
		if (VME_OFFSET(entry)) {
			/*
			 * If the map entry has been split and the object now
			 * appears several times in the VM map, we don't want
			 * to count the object's resident_page_count more than
			 * once.  We count it only for the first one, starting
			 * at offset 0 and ignore the other VM map entries.
			 */
			continue;
		}
		resident_count = object->resident_page_count;
		if ((VME_OFFSET(entry) / PAGE_SIZE) >= resident_count) {
			resident_count = 0;
		} else {
			resident_count -= (VME_OFFSET(entry) / PAGE_SIZE);
		}

		volatile_virtual_size += entry->vme_end - entry->vme_start;
		volatile_resident_count += resident_count;
		if (object->pager) {
			volatile_compressed_count +=
				vm_compressor_pager_get_count(object->pager);
		}
		pmap_compressed_bytes = 0;
		pmap_resident_bytes =
			pmap_query_resident(map->pmap,
					    entry->vme_start,
					    entry->vme_end,
					    &pmap_compressed_bytes);
		volatile_pmap_count += (pmap_resident_bytes / PAGE_SIZE);
		volatile_compressed_pmap_count += (pmap_compressed_bytes
						   / PAGE_SIZE);
	}

	/* map is still locked on return */

	*volatile_virtual_size_p = volatile_virtual_size;
	*volatile_resident_size_p = volatile_resident_count * PAGE_SIZE;
	*volatile_compressed_size_p = volatile_compressed_count * PAGE_SIZE;
	*volatile_pmap_size_p = volatile_pmap_count * PAGE_SIZE;
	*volatile_compressed_pmap_size_p = volatile_compressed_pmap_count * PAGE_SIZE;

	return KERN_SUCCESS;
}