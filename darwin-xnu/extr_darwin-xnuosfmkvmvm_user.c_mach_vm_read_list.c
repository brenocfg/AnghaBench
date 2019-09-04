#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_map_size_t ;
typedef  int /*<<< orphan*/  vm_map_copy_t ;
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ natural_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  TYPE_1__* mach_vm_read_entry_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_5__ {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {scalar_t__ size; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ VM_MAP_ENTRY_MAX ; 
 scalar_t__ VM_MAP_NULL ; 
 TYPE_3__* current_task () ; 
 int /*<<< orphan*/  vm_map_copy_discard (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_copyin (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_map_copyout (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

kern_return_t
mach_vm_read_list(
	vm_map_t			map,
	mach_vm_read_entry_t		data_list,
	natural_t			count)
{
	mach_msg_type_number_t	i;
	kern_return_t	error;
	vm_map_copy_t	copy;

	if (map == VM_MAP_NULL ||
	    count > VM_MAP_ENTRY_MAX)
		return(KERN_INVALID_ARGUMENT);

	error = KERN_SUCCESS;
	for(i=0; i<count; i++) {
		vm_map_address_t map_addr;
		vm_map_size_t map_size;

		map_addr = (vm_map_address_t)(data_list[i].address);
		map_size = (vm_map_size_t)(data_list[i].size);

		if(map_size != 0) {
			error = vm_map_copyin(map,
					map_addr,
					map_size,
					FALSE,	/* src_destroy */
					&copy);
			if (KERN_SUCCESS == error) {
				error = vm_map_copyout(
						current_task()->map, 
						&map_addr,
						copy);
				if (KERN_SUCCESS == error) {
					data_list[i].address = map_addr;
					continue;
				}
				vm_map_copy_discard(copy);
			}
		}
		data_list[i].address = (mach_vm_address_t)0;
		data_list[i].size = (mach_vm_size_t)0;
	}
	return(error);
}