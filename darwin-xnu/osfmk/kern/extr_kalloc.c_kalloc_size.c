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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  kalloc_map ; 
 scalar_t__ kalloc_map_max ; 
 scalar_t__ kalloc_map_min ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  vm_map_lock_read (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_lookup_kalloc_entry_locked (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (int /*<<< orphan*/ ) ; 
 scalar_t__ zone_element_size (void*,int /*<<< orphan*/ *) ; 

vm_size_t
kalloc_size(
		void 		*addr)
{
	vm_map_t 		map;
	vm_size_t 		size;

	size = zone_element_size(addr, NULL);
	if (size) {
		return size;
	}
	if (((vm_offset_t)addr >= kalloc_map_min) && ((vm_offset_t)addr < kalloc_map_max)) {
		map = kalloc_map;
	} else {
		map = kernel_map;
	}
	vm_map_lock_read(map);
	size = vm_map_lookup_kalloc_entry_locked(map, addr);
	vm_map_unlock_read(map);
	return size;
}