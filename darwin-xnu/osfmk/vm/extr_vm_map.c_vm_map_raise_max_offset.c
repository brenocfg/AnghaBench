#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {scalar_t__ max_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MACH_VM_MAX_ADDRESS ; 
 scalar_t__ VM_MAX_ADDRESS ; 
 int /*<<< orphan*/  vm_map_is_64bit (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 

kern_return_t
vm_map_raise_max_offset(
	vm_map_t	map,
	vm_map_offset_t	new_max_offset)
{
	kern_return_t	ret;

	vm_map_lock(map);
	ret = KERN_INVALID_ADDRESS;

	if (new_max_offset >= map->max_offset) {
		if (!vm_map_is_64bit(map)) {
			if (new_max_offset <= (vm_map_offset_t)VM_MAX_ADDRESS) {
				map->max_offset = new_max_offset;
				ret = KERN_SUCCESS;
			}
		} else {
			if (new_max_offset <= (vm_map_offset_t)MACH_VM_MAX_ADDRESS) {
				map->max_offset = new_max_offset;
				ret = KERN_SUCCESS;
			}
		}
	}

	vm_map_unlock(map);
	return ret;
}