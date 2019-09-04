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
typedef  TYPE_1__* vm_shared_region_slide_info_entry_v3_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int mach_vm_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {scalar_t__ page_size; int page_starts_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE_FOR_SR_SLIDE ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vm_shared_region_slide_sanity_check_v3(vm_shared_region_slide_info_entry_v3_t s_info, mach_vm_size_t slide_info_size)
{
	if (s_info->page_size != PAGE_SIZE_FOR_SR_SLIDE) {
		printf("vm_shared_region_slide_sanity_check_v3: s_info->page_size != PAGE_SIZE_FOR_SR_SL 0x%llx != 0x%llx\n", (uint64_t)s_info->page_size, (uint64_t)PAGE_SIZE_FOR_SR_SLIDE);
		return KERN_FAILURE;
	}

	uint32_t page_starts_count = s_info->page_starts_count;
	mach_vm_size_t num_trailing_entries = page_starts_count;
	mach_vm_size_t trailing_size = num_trailing_entries << 1;
	mach_vm_size_t required_size = sizeof(*s_info) + trailing_size;
	if (required_size < sizeof(*s_info)) {
		printf("vm_shared_region_slide_sanity_check_v3: required_size != sizeof(*s_info) 0x%llx != 0x%llx\n", (uint64_t)required_size, (uint64_t)sizeof(*s_info));
		return KERN_FAILURE;
	}

	if (required_size > slide_info_size) {
		printf("vm_shared_region_slide_sanity_check_v3: required_size != slide_info_size 0x%llx != 0x%llx\n", (uint64_t)required_size, (uint64_t)slide_info_size);
		return KERN_FAILURE;
	}

	return KERN_SUCCESS;
}