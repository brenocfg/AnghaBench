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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ VM_MAP_NULL ; 
 int /*<<< orphan*/  vm_map_remove_upl (scalar_t__,int /*<<< orphan*/ ) ; 

kern_return_t
vm_upl_unmap(
	vm_map_t		map,
	upl_t 			upl)
{
	if (VM_MAP_NULL == map)
		return KERN_INVALID_ARGUMENT;

	return (vm_map_remove_upl(map, upl));
}