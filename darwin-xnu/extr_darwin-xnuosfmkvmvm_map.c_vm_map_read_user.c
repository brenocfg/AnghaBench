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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_address_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ current_map () ; 
 int /*<<< orphan*/  vm_map_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_reference (scalar_t__) ; 
 scalar_t__ vm_map_switch (scalar_t__) ; 

kern_return_t
vm_map_read_user(
	vm_map_t		map,
	vm_map_address_t	src_addr,
	void			*dst_p,
	vm_size_t		size)
{
	kern_return_t	kr = KERN_SUCCESS;

	if(current_map() == map) {
		if (copyin(src_addr, dst_p, size)) {
			kr = KERN_INVALID_ADDRESS;
		}
	} else {
		vm_map_t	oldmap;

		/* take on the identity of the target map while doing */
		/* the transfer */

		vm_map_reference(map);
		oldmap = vm_map_switch(map);
		if (copyin(src_addr, dst_p, size)) {
			kr = KERN_INVALID_ADDRESS;
		}
		vm_map_switch(oldmap);
		vm_map_deallocate(map);
	}
	return kr;
}