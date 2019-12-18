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
 int /*<<< orphan*/  __flush_invalidate_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  __invalidate_dcache_range (unsigned long,unsigned long) ; 

void consistent_sync(void *vaddr, size_t size, int direction)
{
	switch (direction) {
	case PCI_DMA_NONE:
		BUG();
	case PCI_DMA_FROMDEVICE:        /* invalidate only */
		__invalidate_dcache_range((unsigned long)vaddr,
				          (unsigned long)size);
		break;

	case PCI_DMA_TODEVICE:          /* writeback only */
	case PCI_DMA_BIDIRECTIONAL:     /* writeback and invalidate */
		__flush_invalidate_dcache_range((unsigned long)vaddr,
				    		(unsigned long)size);
		break;
	}
}