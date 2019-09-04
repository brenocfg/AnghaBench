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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_object_t ;

/* Variables and functions */
 scalar_t__ VM_PAGE_OBJECT (int /*<<< orphan*/ ) ; 
 scalar_t__ compressor_object ; 
 scalar_t__ kernel_object ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 scalar_t__ vm_submap_object ; 

void
vm_page_check_pageable_safe(vm_page_t page)
{
	vm_object_t	page_object;

	page_object = VM_PAGE_OBJECT(page);

	if (page_object == kernel_object) {
		panic("vm_page_check_pageable_safe: trying to add page" \
			 "from kernel object (%p) to pageable queue", kernel_object);
	}

	if (page_object == compressor_object) {
		panic("vm_page_check_pageable_safe: trying to add page" \
			 "from compressor object (%p) to pageable queue", compressor_object);
	}

	if (page_object == vm_submap_object) {
		panic("vm_page_check_pageable_safe: trying to add page" \
			"from submap object (%p) to pageable queue", vm_submap_object);
	}
}