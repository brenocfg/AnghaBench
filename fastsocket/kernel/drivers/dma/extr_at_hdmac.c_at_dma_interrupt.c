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
struct at_dma_chan {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  error_status; int /*<<< orphan*/  mask; } ;
struct TYPE_2__ {int chancnt; int /*<<< orphan*/  dev; } ;
struct at_dma {struct at_dma_chan* chan; TYPE_1__ dma_common; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int AT_DMA_CBTC (int) ; 
 int AT_DMA_ERR (int) ; 
 int /*<<< orphan*/  CHDR ; 
 int /*<<< orphan*/  EBCIMR ; 
 int /*<<< orphan*/  EBCISR ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int dma_readl (struct at_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct at_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t at_dma_interrupt(int irq, void *dev_id)
{
	struct at_dma		*atdma = (struct at_dma *)dev_id;
	struct at_dma_chan	*atchan;
	int			i;
	u32			status, pending, imr;
	int			ret = IRQ_NONE;

	do {
		imr = dma_readl(atdma, EBCIMR);
		status = dma_readl(atdma, EBCISR);
		pending = status & imr;

		if (!pending)
			break;

		dev_vdbg(atdma->dma_common.dev,
			"interrupt: status = 0x%08x, 0x%08x, 0x%08x\n",
			 status, imr, pending);

		for (i = 0; i < atdma->dma_common.chancnt; i++) {
			atchan = &atdma->chan[i];
			if (pending & (AT_DMA_CBTC(i) | AT_DMA_ERR(i))) {
				if (pending & AT_DMA_ERR(i)) {
					/* Disable channel on AHB error */
					dma_writel(atdma, CHDR, atchan->mask);
					/* Give information to tasklet */
					set_bit(0, &atchan->error_status);
				}
				tasklet_schedule(&atchan->tasklet);
				ret = IRQ_HANDLED;
			}
		}

	} while (pending);

	return ret;
}