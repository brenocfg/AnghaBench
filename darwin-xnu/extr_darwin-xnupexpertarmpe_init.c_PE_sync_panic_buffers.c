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
 int /*<<< orphan*/  CleanPoC_DcacheRegion_Force (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gPanicBase ; 
 int /*<<< orphan*/  gPanicSize ; 

void
PE_sync_panic_buffers(void)
{
	/*
	 * rdar://problem/26453070:
	 * The iBoot panic region is write-combined on arm64.  We must flush dirty lines
	 * from L1/L2 as late as possible before reset, with no further reads of the panic
	 * region between the flush and the reset.  Some targets have an additional memcache (L3),
	 * and a read may bring dirty lines out of L3 and back into L1/L2, causing the lines to
	 * be discarded on reset.  If we can make sure the lines are flushed to L3/DRAM,
	 * the platform reset handler will flush any L3.
	 */
	if (gPanicBase)
		CleanPoC_DcacheRegion_Force(gPanicBase, gPanicSize);
}