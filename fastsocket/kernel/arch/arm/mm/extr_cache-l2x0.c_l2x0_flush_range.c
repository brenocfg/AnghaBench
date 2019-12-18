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
 int /*<<< orphan*/  L2X0_CLEAN_INV_LINE_PA ; 
 int /*<<< orphan*/  cache_sync () ; 
 int /*<<< orphan*/  sync_writel (unsigned long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l2x0_flush_range(unsigned long start, unsigned long end)
{
	unsigned long addr;

	start &= ~(CACHE_LINE_SIZE - 1);
	for (addr = start; addr < end; addr += CACHE_LINE_SIZE)
		sync_writel(addr, L2X0_CLEAN_INV_LINE_PA, 1);
	cache_sync();
}