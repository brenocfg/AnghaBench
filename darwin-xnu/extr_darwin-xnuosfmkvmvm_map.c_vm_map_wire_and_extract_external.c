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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ VM_MAP_PAGE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_wire_nested (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vm_tag_bt () ; 

kern_return_t
vm_map_wire_and_extract_external(
	vm_map_t	map,
	vm_map_offset_t	start,
	vm_prot_t	caller_prot,
	boolean_t	user_wire,
	ppnum_t		*physpage_p)
{
	kern_return_t	kret;

	kret = vm_map_wire_nested(map,
				  start,
				  start+VM_MAP_PAGE_SIZE(map),
				  caller_prot,
				  vm_tag_bt(),
				  user_wire,
				  (pmap_t)NULL,
				  0,
				  physpage_p);
	if (kret != KERN_SUCCESS &&
	    physpage_p != NULL) {
		*physpage_p = 0;
	}
	return kret;
}