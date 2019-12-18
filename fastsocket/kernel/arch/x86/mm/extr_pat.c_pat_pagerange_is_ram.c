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
typedef  unsigned long resource_size_t ;

/* Variables and functions */
 unsigned long ISA_END_ADDRESS ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ page_is_ram (unsigned long) ; 

__attribute__((used)) static int pat_pagerange_is_ram(resource_size_t start, resource_size_t end)
{
	int ram_page = 0, not_rampage = 0;
	unsigned long page_nr;

	for (page_nr = (start >> PAGE_SHIFT); page_nr < (end >> PAGE_SHIFT);
	     ++page_nr) {
		/*
		 * For legacy reasons, physical address range in the legacy ISA
		 * region is tracked as non-RAM. This will allow users of
		 * /dev/mem to map portions of legacy ISA region, even when
		 * some of those portions are listed(or not even listed) with
		 * different e820 types(RAM/reserved/..)
		 */
		if (page_nr >= (ISA_END_ADDRESS >> PAGE_SHIFT) &&
		    page_is_ram(page_nr))
			ram_page = 1;
		else
			not_rampage = 1;

		if (ram_page == not_rampage)
			return -1;
	}

	return ram_page;
}