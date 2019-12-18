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
#define  PCI_DMA_BIDIRECTIONAL 131 
#define  PCI_DMA_FROMDEVICE 130 
#define  PCI_DMA_NONE 129 
#define  PCI_DMA_TODEVICE 128 
 int /*<<< orphan*/  frv_cache_invalidate (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  frv_dcache_writeback (unsigned long,unsigned long) ; 

void consistent_sync(void *vaddr, size_t size, int direction)
{
	unsigned long start = (unsigned long) vaddr;
	unsigned long end   = start + size;

	switch (direction) {
	case PCI_DMA_NONE:
		BUG();
	case PCI_DMA_FROMDEVICE:	/* invalidate only */
		frv_cache_invalidate(start, end);
		break;
	case PCI_DMA_TODEVICE:		/* writeback only */
		frv_dcache_writeback(start, end);
		break;
	case PCI_DMA_BIDIRECTIONAL:	/* writeback and invalidate */
		frv_dcache_writeback(start, end);
		break;
	}
}