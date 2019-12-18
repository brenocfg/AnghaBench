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
 unsigned long max_low_pfn ; 
 unsigned long min_low_pfn ; 

int page_is_ram(unsigned long pagenr)
{
	if (pagenr >= min_low_pfn && pagenr < max_low_pfn)
		return 1;
	else
		return 0;
}