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
typedef  int /*<<< orphan*/  vm_page_info_t ;
struct TYPE_2__ {int disposition; int ref_count; } ;
typedef  TYPE_1__ vm_page_info_basic_data_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VM_PAGE_INFO_BASIC ; 
 int /*<<< orphan*/  VM_PAGE_INFO_BASIC_COUNT ; 
 scalar_t__ vm_map_page_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
vm_map_page_query_internal(
	vm_map_t	target_map,
	vm_map_offset_t	offset,
	int		*disposition,
	int		*ref_count)
{
	kern_return_t			kr;
	vm_page_info_basic_data_t	info;
	mach_msg_type_number_t		count;

	count = VM_PAGE_INFO_BASIC_COUNT;
	kr = vm_map_page_info(target_map,
			      offset,
			      VM_PAGE_INFO_BASIC,
			      (vm_page_info_t) &info,
			      &count);
	if (kr == KERN_SUCCESS) {
		*disposition = info.disposition;
		*ref_count = info.ref_count;
	} else {
		*disposition = 0;
		*ref_count = 0;
	}

	return kr;
}