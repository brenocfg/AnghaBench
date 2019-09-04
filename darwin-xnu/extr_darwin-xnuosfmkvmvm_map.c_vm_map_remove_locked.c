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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
vm_map_remove_locked(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_map_offset_t	end,
	boolean_t	flags)
{
	kern_return_t	result;

	VM_MAP_RANGE_CHECK(map, start, end);
	result = vm_map_delete(map, start, end, flags, VM_MAP_NULL);
	return(result);
}