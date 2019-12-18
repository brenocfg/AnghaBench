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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DMA_BASE ; 
 scalar_t__ DMA_DISR ; 
 int IMX_DMA_CHANNELS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  dma_err_handler (int,void*) ; 
 int /*<<< orphan*/  dma_irq_handle_channel (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static irqreturn_t dma_irq_handler(int irq, void *dev_id)
{
	int i, disr;

#ifdef CONFIG_ARCH_MX2
	dma_err_handler(irq, dev_id);
#endif

	disr = __raw_readl(DMA_BASE + DMA_DISR);

	pr_debug("imxdma: dma_irq_handler called, disr=0x%08x\n",
		     disr);

	__raw_writel(disr, DMA_BASE + DMA_DISR);
	for (i = 0; i < IMX_DMA_CHANNELS; i++) {
		if (disr & (1 << i))
			dma_irq_handle_channel(i);
	}

	return IRQ_HANDLED;
}