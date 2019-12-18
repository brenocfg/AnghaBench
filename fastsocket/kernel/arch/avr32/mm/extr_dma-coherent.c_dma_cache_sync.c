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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 scalar_t__ P2SEG ; 
 scalar_t__ PXSEG (void*) ; 
 int /*<<< orphan*/  clean_dcache_region (void*,size_t) ; 
 int /*<<< orphan*/  flush_dcache_region (void*,size_t) ; 
 int /*<<< orphan*/  invalidate_dcache_region (void*,size_t) ; 

void dma_cache_sync(struct device *dev, void *vaddr, size_t size, int direction)
{
	/*
	 * No need to sync an uncached area
	 */
	if (PXSEG(vaddr) == P2SEG)
		return;

	switch (direction) {
	case DMA_FROM_DEVICE:		/* invalidate only */
		invalidate_dcache_region(vaddr, size);
		break;
	case DMA_TO_DEVICE:		/* writeback only */
		clean_dcache_region(vaddr, size);
		break;
	case DMA_BIDIRECTIONAL:		/* writeback and invalidate */
		flush_dcache_region(vaddr, size);
		break;
	default:
		BUG();
	}
}