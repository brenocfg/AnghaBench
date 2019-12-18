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
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 unsigned long __pa (void const*) ; 
 void dmac_clean_range (void const*,void const*) ; 
 void dmac_flush_range (void const*,void const*) ; 
 void dmac_inv_range (void const*,void const*) ; 
 void outer_clean_range (unsigned long,unsigned long) ; 
 void outer_flush_range (unsigned long,unsigned long) ; 
 void outer_inv_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  virt_addr_valid (void const*) ; 

void dma_cache_maint(const void *start, size_t size, int direction)
{
	void (*inner_op)(const void *, const void *);
	void (*outer_op)(unsigned long, unsigned long);

	BUG_ON(!virt_addr_valid(start) || !virt_addr_valid(start + size - 1));

	switch (direction) {
	case DMA_FROM_DEVICE:		/* invalidate only */
		inner_op = dmac_inv_range;
		outer_op = outer_inv_range;
		break;
	case DMA_TO_DEVICE:		/* writeback only */
		inner_op = dmac_clean_range;
		outer_op = outer_clean_range;
		break;
	case DMA_BIDIRECTIONAL:		/* writeback and invalidate */
		inner_op = dmac_flush_range;
		outer_op = outer_flush_range;
		break;
	default:
		BUG();
	}

	inner_op(start, start + size);
	outer_op(__pa(start), __pa(start) + size);
}