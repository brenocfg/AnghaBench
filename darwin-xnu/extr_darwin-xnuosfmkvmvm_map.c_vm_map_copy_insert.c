#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_entry_t ;
typedef  int /*<<< orphan*/  vm_map_copy_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  vm_map_copy_entry_unlink (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vm_map_copy_first_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copy_to_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_copy_zone ; 
 int /*<<< orphan*/  vm_map_store_entry_link (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_map_copy_insert(
	vm_map_t	map,
	vm_map_entry_t	after_where,
	vm_map_copy_t	copy)
{
	vm_map_entry_t	entry;

	while (vm_map_copy_first_entry(copy) != vm_map_copy_to_entry(copy)) {
		entry = vm_map_copy_first_entry(copy);
		vm_map_copy_entry_unlink(copy, entry);
		vm_map_store_entry_link(map, after_where, entry,
					VM_MAP_KERNEL_FLAGS_NONE);
		after_where = entry;
	}
	zfree(vm_map_copy_zone, copy);
}