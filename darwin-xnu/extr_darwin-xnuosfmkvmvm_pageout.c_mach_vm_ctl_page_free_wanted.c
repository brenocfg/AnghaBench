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

/* Variables and functions */
 unsigned int vm_page_free_count ; 
 unsigned int vm_page_free_target ; 

unsigned int
mach_vm_ctl_page_free_wanted(void)
{
	unsigned int page_free_target, page_free_count, page_free_wanted;

	page_free_target = vm_page_free_target;
	page_free_count = vm_page_free_count;
	if (page_free_target > page_free_count) {
		page_free_wanted = page_free_target - page_free_count;
	} else {
		page_free_wanted = 0;
	}

	return page_free_wanted;
}