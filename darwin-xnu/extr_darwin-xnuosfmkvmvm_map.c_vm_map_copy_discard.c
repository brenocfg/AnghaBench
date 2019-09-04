#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_entry_t ;
typedef  TYPE_2__* vm_map_copy_t ;
struct TYPE_18__ {int type; scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/  cpy_object; } ;
struct TYPE_17__ {int /*<<< orphan*/  is_sub_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  VME_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  VME_SUBMAP (TYPE_1__*) ; 
#define  VM_MAP_COPY_ENTRY_LIST 130 
#define  VM_MAP_COPY_KERNEL_BUFFER 129 
 TYPE_2__* VM_MAP_COPY_NULL ; 
#define  VM_MAP_COPY_OBJECT 128 
 scalar_t__ cpy_kdata_hdr_sz ; 
 int /*<<< orphan*/  kfree (TYPE_2__*,scalar_t__) ; 
 scalar_t__ msg_ool_size_small ; 
 int /*<<< orphan*/  panic (char*,long long,long long) ; 
 int /*<<< orphan*/  vm_map_copy_entry_dispose (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_copy_entry_unlink (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* vm_map_copy_first_entry (TYPE_2__*) ; 
 TYPE_1__* vm_map_copy_to_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_copy_zone ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
vm_map_copy_discard(
	vm_map_copy_t	copy)
{
	if (copy == VM_MAP_COPY_NULL)
		return;

	switch (copy->type) {
	case VM_MAP_COPY_ENTRY_LIST:
		while (vm_map_copy_first_entry(copy) !=
		       vm_map_copy_to_entry(copy)) {
			vm_map_entry_t	entry = vm_map_copy_first_entry(copy);

			vm_map_copy_entry_unlink(copy, entry);
			if (entry->is_sub_map) {
				vm_map_deallocate(VME_SUBMAP(entry));
			} else {
				vm_object_deallocate(VME_OBJECT(entry));
			}
			vm_map_copy_entry_dispose(copy, entry);
		}
		break;
        case VM_MAP_COPY_OBJECT:
		vm_object_deallocate(copy->cpy_object);
		break;
	case VM_MAP_COPY_KERNEL_BUFFER:

		/*
		 * The vm_map_copy_t and possibly the data buffer were
		 * allocated by a single call to kalloc(), i.e. the
		 * vm_map_copy_t was not allocated out of the zone.
		 */
		if (copy->size > msg_ool_size_small || copy->offset)
			panic("Invalid vm_map_copy_t sz:%lld, ofst:%lld",
			      (long long)copy->size, (long long)copy->offset);
		kfree(copy, copy->size + cpy_kdata_hdr_sz);
		return;
	}
	zfree(vm_map_copy_zone, copy);
}