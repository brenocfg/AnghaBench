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
typedef  int /*<<< orphan*/  vm_sync_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_msync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_msync(
	vm_map_t		map,
	mach_vm_address_t	address,
	mach_vm_size_t	size,
	vm_sync_t		sync_flags)
{

	if (map == VM_MAP_NULL)
		return(KERN_INVALID_TASK);

	return vm_map_msync(map, (vm_map_address_t)address,
			(vm_map_size_t)size, sync_flags);
}