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
struct TYPE_2__ {int /*<<< orphan*/  chan_id; int /*<<< orphan*/  device; } ;
struct at_dma_chan {TYPE_1__ chan_common; } ;
struct at_dma {int dummy; } ;

/* Variables and functions */
 int AT_DMA_CBTC (int /*<<< orphan*/ ) ; 
 int AT_DMA_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBCIDR ; 
 int /*<<< orphan*/  EBCIER ; 
 int /*<<< orphan*/  dma_writel (struct at_dma*,int /*<<< orphan*/ ,int) ; 
 struct at_dma* to_at_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atc_setup_irq(struct at_dma_chan *atchan, int on)
{
	struct at_dma	*atdma = to_at_dma(atchan->chan_common.device);
	u32		ebci;

	/* enable interrupts on buffer chain completion & error */
	ebci =    AT_DMA_CBTC(atchan->chan_common.chan_id)
		| AT_DMA_ERR(atchan->chan_common.chan_id);
	if (on)
		dma_writel(atdma, EBCIER, ebci);
	else
		dma_writel(atdma, EBCIDR, ebci);
}