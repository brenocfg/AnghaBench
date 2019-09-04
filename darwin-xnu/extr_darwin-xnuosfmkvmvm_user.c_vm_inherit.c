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
typedef  scalar_t__ vm_map_t ;
typedef  scalar_t__ vm_inherit_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VM_INHERIT_LAST_VALID ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_inherit (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_trunc_page (scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
vm_inherit(
	vm_map_t		map,
	vm_offset_t		start,
	vm_size_t		size,
	vm_inherit_t		new_inheritance)
{
	if ((map == VM_MAP_NULL) || (start + size < start) ||
	    (new_inheritance > VM_INHERIT_LAST_VALID))
                return(KERN_INVALID_ARGUMENT);

	if (size == 0)
		return KERN_SUCCESS;

	return(vm_map_inherit(map,
			      vm_map_trunc_page(start,
						VM_MAP_PAGE_MASK(map)),
			      vm_map_round_page(start+size,
						VM_MAP_PAGE_MASK(map)),
			      new_inheritance));
}