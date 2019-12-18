#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int dev_id; int next_lch; int /*<<< orphan*/ * callback; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR (int) ; 
 int /*<<< orphan*/  CICR (int) ; 
 int /*<<< orphan*/  CSR (int) ; 
 int /*<<< orphan*/  IRQENABLE_L0 ; 
 int /*<<< orphan*/  IRQSTATUS_L0 ; 
 int OMAP2_DMA_CSR_CLEAR_MASK ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_class_is_omap2 () ; 
 TYPE_1__* dma_chan ; 
 int /*<<< orphan*/  dma_chan_lock ; 
 int dma_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_clear_dma (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap_free_dma(int lch)
{
	unsigned long flags;

	if (dma_chan[lch].dev_id == -1) {
		pr_err("omap_dma: trying to free unallocated DMA channel %d\n",
		       lch);
		return;
	}

	if (cpu_class_is_omap1()) {
		/* Disable all DMA interrupts for the channel. */
		dma_write(0, CICR(lch));
		/* Make sure the DMA transfer is stopped. */
		dma_write(0, CCR(lch));
	}

	if (cpu_class_is_omap2()) {
		u32 val;

		spin_lock_irqsave(&dma_chan_lock, flags);
		/* Disable interrupts */
		val = dma_read(IRQENABLE_L0);
		val &= ~(1 << lch);
		dma_write(val, IRQENABLE_L0);
		spin_unlock_irqrestore(&dma_chan_lock, flags);

		/* Clear the CSR register and IRQ status register */
		dma_write(OMAP2_DMA_CSR_CLEAR_MASK, CSR(lch));
		dma_write(1 << lch, IRQSTATUS_L0);

		/* Disable all DMA interrupts for the channel. */
		dma_write(0, CICR(lch));

		/* Make sure the DMA transfer is stopped. */
		dma_write(0, CCR(lch));
		omap_clear_dma(lch);
	}

	spin_lock_irqsave(&dma_chan_lock, flags);
	dma_chan[lch].dev_id = -1;
	dma_chan[lch].next_lch = -1;
	dma_chan[lch].callback = NULL;
	spin_unlock_irqrestore(&dma_chan_lock, flags);
}