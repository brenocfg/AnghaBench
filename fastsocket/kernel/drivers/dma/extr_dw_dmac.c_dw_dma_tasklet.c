#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dw_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int chancnt; int /*<<< orphan*/  dev; } ;
struct dw_dma {int /*<<< orphan*/  all_chan_mask; struct dw_dma_chan* chan; TYPE_1__ dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  ERROR; int /*<<< orphan*/  BLOCK; int /*<<< orphan*/  XFER; } ;
struct TYPE_5__ {int /*<<< orphan*/  ERROR; int /*<<< orphan*/  XFER; int /*<<< orphan*/  BLOCK; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DMA_IS_CYCLIC ; 
 TYPE_3__ MASK ; 
 TYPE_2__ RAW ; 
 int /*<<< orphan*/  channel_set_bit (struct dw_dma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_handle_cyclic (struct dw_dma*,struct dw_dma_chan*,int,int,int) ; 
 int /*<<< orphan*/  dwc_handle_error (struct dw_dma*,struct dw_dma_chan*) ; 
 int /*<<< orphan*/  dwc_scan_descriptors (struct dw_dma*,struct dw_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_dma_tasklet(unsigned long data)
{
	struct dw_dma *dw = (struct dw_dma *)data;
	struct dw_dma_chan *dwc;
	u32 status_block;
	u32 status_xfer;
	u32 status_err;
	int i;

	status_block = dma_readl(dw, RAW.BLOCK);
	status_xfer = dma_readl(dw, RAW.XFER);
	status_err = dma_readl(dw, RAW.ERROR);

	dev_vdbg(dw->dma.dev, "tasklet: status_block=%x status_err=%x\n",
			status_block, status_err);

	for (i = 0; i < dw->dma.chancnt; i++) {
		dwc = &dw->chan[i];
		spin_lock(&dwc->lock);
		if (test_bit(DW_DMA_IS_CYCLIC, &dwc->flags))
			dwc_handle_cyclic(dw, dwc, status_block, status_err,
					status_xfer);
		else if (status_err & (1 << i))
			dwc_handle_error(dw, dwc);
		else if ((status_block | status_xfer) & (1 << i))
			dwc_scan_descriptors(dw, dwc);
		spin_unlock(&dwc->lock);
	}

	/*
	 * Re-enable interrupts. Block Complete interrupts are only
	 * enabled if the INT_EN bit in the descriptor is set. This
	 * will trigger a scan before the whole list is done.
	 */
	channel_set_bit(dw, MASK.XFER, dw->all_chan_mask);
	channel_set_bit(dw, MASK.BLOCK, dw->all_chan_mask);
	channel_set_bit(dw, MASK.ERROR, dw->all_chan_mask);
}