#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_copy_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ VM_MAP_NULL ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  vm_map_copy_discard (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copy_overwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
mach_vm_read_overwrite(
	vm_map_t		map,
	mach_vm_address_t	address,
	mach_vm_size_t	size,
	mach_vm_address_t	data,
	mach_vm_size_t	*data_size)
{
	kern_return_t	error;
	vm_map_copy_t	copy;

	if (map == VM_MAP_NULL)
		return(KERN_INVALID_ARGUMENT);

	error = vm_map_copyin(map, (vm_map_address_t)address,
				(vm_map_size_t)size, FALSE, &copy);

	if (KERN_SUCCESS == error) {
		error = vm_map_copy_overwrite(current_thread()->map,
 					(vm_map_address_t)data, 
					copy, FALSE);
		if (KERN_SUCCESS == error) {
			*data_size = size;
			return error;
		}
		vm_map_copy_discard(copy);
	}
	return(error);
}