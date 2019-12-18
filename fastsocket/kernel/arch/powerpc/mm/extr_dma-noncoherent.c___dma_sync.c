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
 int /*<<< orphan*/  BUG () ; 
#define  DMA_BIDIRECTIONAL 131 
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int /*<<< orphan*/  L1_CACHE_BYTES ; 
 int /*<<< orphan*/  clean_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  invalidate_dcache_range (unsigned long,unsigned long) ; 

void __dma_sync(void *vaddr, size_t size, int direction)
{
	unsigned long start = (unsigned long)vaddr;
	unsigned long end   = start + size;

	switch (direction) {
	case DMA_NONE:
		BUG();
	case DMA_FROM_DEVICE:
		/*
		 * invalidate only when cache-line aligned otherwise there is
		 * the potential for discarding uncommitted data from the cache
		 */
		if ((start & (L1_CACHE_BYTES - 1)) || (size & (L1_CACHE_BYTES - 1)))
			flush_dcache_range(start, end);
		else
			invalidate_dcache_range(start, end);
		break;
	case DMA_TO_DEVICE:		/* writeback only */
		clean_dcache_range(start, end);
		break;
	case DMA_BIDIRECTIONAL:	/* writeback and invalidate */
		flush_dcache_range(start, end);
		break;
	}
}