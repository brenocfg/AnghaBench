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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CCR (int) ; 
 int /*<<< orphan*/  CCR2 (int) ; 
 int /*<<< orphan*/  CEN (int) ; 
 int /*<<< orphan*/  CFN (int) ; 
 int /*<<< orphan*/  CSDP (int) ; 
 int OMAP_DMA_SYNC_BLOCK ; 
 int OMAP_DMA_SYNC_FRAME ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 

void omap_set_dma_transfer_params(int lch, int data_type, int elem_count,
				  int frame_count, int sync_mode,
				  int dma_trigger, int src_or_dst_synch)
{
	u32 l;

	l = dma_read(CSDP(lch));
	l &= ~0x03;
	l |= data_type;
	dma_write(l, CSDP(lch));

	if (cpu_class_is_omap1()) {
		u16 ccr;

		ccr = dma_read(CCR(lch));
		ccr &= ~(1 << 5);
		if (sync_mode == OMAP_DMA_SYNC_FRAME)
			ccr |= 1 << 5;
		dma_write(ccr, CCR(lch));

		ccr = dma_read(CCR2(lch));
		ccr &= ~(1 << 2);
		if (sync_mode == OMAP_DMA_SYNC_BLOCK)
			ccr |= 1 << 2;
		dma_write(ccr, CCR2(lch));
	}

	if (cpu_class_is_omap2() && dma_trigger) {
		u32 val;

		val = dma_read(CCR(lch));

		/* DMA_SYNCHRO_CONTROL_UPPER depends on the channel number */
		val &= ~((3 << 19) | 0x1f);
		val |= (dma_trigger & ~0x1f) << 14;
		val |= dma_trigger & 0x1f;

		if (sync_mode & OMAP_DMA_SYNC_FRAME)
			val |= 1 << 5;
		else
			val &= ~(1 << 5);

		if (sync_mode & OMAP_DMA_SYNC_BLOCK)
			val |= 1 << 18;
		else
			val &= ~(1 << 18);

		if (src_or_dst_synch)
			val |= 1 << 24;		/* source synch */
		else
			val &= ~(1 << 24);	/* dest synch */

		dma_write(val, CCR(lch));
	}

	dma_write(elem_count, CEN(lch));
	dma_write(frame_count, CFN(lch));
}