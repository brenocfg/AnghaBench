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
 int /*<<< orphan*/  FlushPoU_Dcache () ; 
 int /*<<< orphan*/  InvalidatePoU_Icache () ; 

void dtrace_flush_caches(void)
{
	/* TODO There were some problems with flushing just the cache line that had been modified.
	 * For now, we'll flush the entire cache, until we figure out how to flush just the patched block.
	 */
	FlushPoU_Dcache();
	InvalidatePoU_Icache();
}