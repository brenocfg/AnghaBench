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
struct TYPE_2__ {scalar_t__ vm_page_free_count_init; } ;

/* Variables and functions */
 scalar_t__ COMPRESSOR_FREE_RESERVED_LIMIT ; 
 scalar_t__ VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 scalar_t__ VM_PAGE_FREE_MIN (int) ; 
 scalar_t__ VM_PAGE_FREE_MIN_LIMIT ; 
 scalar_t__ VM_PAGE_FREE_RESERVED_LIMIT ; 
 scalar_t__ VM_PAGE_FREE_TARGET (int) ; 
 scalar_t__ VM_PAGE_FREE_TARGET_LIMIT ; 
 scalar_t__ vm_page_free_min ; 
 scalar_t__ vm_page_free_reserved ; 
 scalar_t__ vm_page_free_target ; 
 scalar_t__ vm_page_throttle_limit ; 
 TYPE_1__ vm_pageout_state ; 

void
vm_page_free_reserve(
	int pages)
{
	int		free_after_reserve;

	if (VM_CONFIG_COMPRESSOR_IS_PRESENT) {

		if ((vm_page_free_reserved + pages + COMPRESSOR_FREE_RESERVED_LIMIT) >= (VM_PAGE_FREE_RESERVED_LIMIT + COMPRESSOR_FREE_RESERVED_LIMIT))
			vm_page_free_reserved = VM_PAGE_FREE_RESERVED_LIMIT + COMPRESSOR_FREE_RESERVED_LIMIT;
		else
			vm_page_free_reserved += (pages + COMPRESSOR_FREE_RESERVED_LIMIT);

	} else {
		if ((vm_page_free_reserved + pages) >= VM_PAGE_FREE_RESERVED_LIMIT)
			vm_page_free_reserved = VM_PAGE_FREE_RESERVED_LIMIT;
		else
			vm_page_free_reserved += pages;
	}
	free_after_reserve = vm_pageout_state.vm_page_free_count_init - vm_page_free_reserved;

	vm_page_free_min = vm_page_free_reserved +
		VM_PAGE_FREE_MIN(free_after_reserve);

	if (vm_page_free_min > VM_PAGE_FREE_MIN_LIMIT)
	        vm_page_free_min = VM_PAGE_FREE_MIN_LIMIT;

	vm_page_free_target = vm_page_free_reserved +
		VM_PAGE_FREE_TARGET(free_after_reserve);

	if (vm_page_free_target > VM_PAGE_FREE_TARGET_LIMIT)
	        vm_page_free_target = VM_PAGE_FREE_TARGET_LIMIT;

	if (vm_page_free_target < vm_page_free_min + 5)
		vm_page_free_target = vm_page_free_min + 5;

	vm_page_throttle_limit = vm_page_free_target - (vm_page_free_target / 2);
}