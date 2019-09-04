#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_shared_region_slide_info_entry_v2_t ;
typedef  int uint32_t ;
typedef  int mach_vm_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {scalar_t__ page_size; int page_starts_count; int page_extras_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE_FOR_SR_SLIDE ; 

__attribute__((used)) static kern_return_t
vm_shared_region_slide_sanity_check_v2(vm_shared_region_slide_info_entry_v2_t s_info, mach_vm_size_t slide_info_size)
{
	if (s_info->page_size != PAGE_SIZE_FOR_SR_SLIDE) {
		return KERN_FAILURE;
	}

	/* Ensure that the slide info doesn't reference any data outside of its bounds. */

	uint32_t page_starts_count = s_info->page_starts_count;
	uint32_t page_extras_count = s_info->page_extras_count;
	mach_vm_size_t num_trailing_entries = page_starts_count + page_extras_count;
	if (num_trailing_entries < page_starts_count) {
		return KERN_FAILURE;
	}

	/* Scale by sizeof(uint16_t). Hard-coding the size simplifies the overflow check. */
	mach_vm_size_t trailing_size = num_trailing_entries << 1;
	if (trailing_size >> 1 != num_trailing_entries) {
		return KERN_FAILURE;
	}

	mach_vm_size_t required_size = sizeof(*s_info) + trailing_size;
	if (required_size < sizeof(*s_info)) {
		return KERN_FAILURE;
	}

	if (required_size > slide_info_size) {
		return KERN_FAILURE;
	}

	return KERN_SUCCESS;
}