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
typedef  int /*<<< orphan*/  vm_page_info_t ;
typedef  int /*<<< orphan*/  vm_page_info_flavor_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_page_range_info_internal (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
vm_map_page_info(
	vm_map_t		map,
	vm_map_offset_t		offset,
	vm_page_info_flavor_t	flavor,
	vm_page_info_t		info,
	mach_msg_type_number_t	*count)
{
	return (vm_map_page_range_info_internal(map,
				       offset, /* start of range */
				       (offset + 1), /* this will get rounded in the call to the page boundary */
				       flavor,
				       info,
				       count));
}