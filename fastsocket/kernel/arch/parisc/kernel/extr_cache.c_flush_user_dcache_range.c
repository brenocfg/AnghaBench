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
 int /*<<< orphan*/  flush_data_cache () ; 
 int /*<<< orphan*/  flush_user_dcache_range_asm (unsigned long,unsigned long) ; 
 unsigned long parisc_cache_flush_threshold ; 

void
flush_user_dcache_range(unsigned long start, unsigned long end)
{
	if ((end - start) < parisc_cache_flush_threshold)
		flush_user_dcache_range_asm(start,end);
	else
		flush_data_cache();
}