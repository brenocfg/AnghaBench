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
 int CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  l2_map_restore_flags (unsigned long) ; 
 int /*<<< orphan*/  l2_map_save_flags (unsigned long) ; 
 unsigned long l2_map_va (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  xsc3_l2_clean_mva (unsigned long) ; 

__attribute__((used)) static void xsc3_l2_clean_range(unsigned long start, unsigned long end)
{
	unsigned long vaddr, flags;

	vaddr = -1;  /* to force the first mapping */
	l2_map_save_flags(flags);

	start &= ~(CACHE_LINE_SIZE - 1);
	while (start < end) {
		vaddr = l2_map_va(start, vaddr, flags);
		xsc3_l2_clean_mva(vaddr);
		start += CACHE_LINE_SIZE;
	}

	l2_map_restore_flags(flags);

	dsb();
}