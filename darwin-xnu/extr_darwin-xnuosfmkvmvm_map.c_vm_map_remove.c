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
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 int /*<<< orphan*/  vm_map_delete (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_lock (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_unlock (scalar_t__) ; 
 scalar_t__ zone_map ; 

kern_return_t
vm_map_remove(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end,
	 boolean_t	flags)
{
	kern_return_t	result;

	vm_map_lock(map);
	VM_MAP_RANGE_CHECK(map, start, end);
	/*
	 * For the zone_map, the kernel controls the allocation/freeing of memory.
	 * Any free to the zone_map should be within the bounds of the map and
	 * should free up memory. If the VM_MAP_RANGE_CHECK() silently converts a
	 * free to the zone_map into a no-op, there is a problem and we should
	 * panic.
	 */
	if ((map == zone_map) && (start == end))
		panic("Nothing being freed to the zone_map. start = end = %p\n", (void *)start);
	result = vm_map_delete(map, start, end, flags, VM_MAP_NULL);
	vm_map_unlock(map);

	return(result);
}