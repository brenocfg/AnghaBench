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
typedef  scalar_t__ u32 ;
struct dw_dma_slave {scalar_t__ dma_dev; scalar_t__ cfg_lo; scalar_t__ cfg_hi; } ;
struct dw_dma_chan {int mask; int completed; int descs_allocated; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ dev; } ;
struct dw_dma {TYPE_1__ dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_submit; } ;
struct dw_desc {int /*<<< orphan*/  lli; TYPE_2__ txd; int /*<<< orphan*/  tx_list; } ;
struct dma_chan {int cookie; struct dw_dma_slave* private; int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  ERROR; int /*<<< orphan*/  BLOCK; int /*<<< orphan*/  XFER; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CFG_HI ; 
 int /*<<< orphan*/  CFG_LO ; 
 int /*<<< orphan*/  CH_EN ; 
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ DWC_CFGH_FIFO_MODE ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_3__ MASK ; 
 int NR_DESCS_PER_CHANNEL ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  chan2parent (struct dma_chan*) ; 
 int /*<<< orphan*/  channel_set_bit (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  channel_writel (struct dw_dma_chan*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_2__*,struct dma_chan*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_desc_put (struct dw_dma_chan*,struct dw_desc*) ; 
 int /*<<< orphan*/  dwc_tx_submit ; 
 struct dw_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int dwc_alloc_chan_resources(struct dma_chan *chan)
{
	struct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	struct dw_dma		*dw = to_dw_dma(chan->device);
	struct dw_desc		*desc;
	struct dw_dma_slave	*dws;
	int			i;
	u32			cfghi;
	u32			cfglo;

	dev_vdbg(chan2dev(chan), "alloc_chan_resources\n");

	/* ASSERT:  channel is idle */
	if (dma_readl(dw, CH_EN) & dwc->mask) {
		dev_dbg(chan2dev(chan), "DMA channel not idle?\n");
		return -EIO;
	}

	dwc->completed = chan->cookie = 1;

	cfghi = DWC_CFGH_FIFO_MODE;
	cfglo = 0;

	dws = chan->private;
	if (dws) {
		/*
		 * We need controller-specific data to set up slave
		 * transfers.
		 */
		BUG_ON(!dws->dma_dev || dws->dma_dev != dw->dma.dev);

		cfghi = dws->cfg_hi;
		cfglo = dws->cfg_lo;
	}
	channel_writel(dwc, CFG_LO, cfglo);
	channel_writel(dwc, CFG_HI, cfghi);

	/*
	 * NOTE: some controllers may have additional features that we
	 * need to initialize here, like "scatter-gather" (which
	 * doesn't mean what you think it means), and status writeback.
	 */

	spin_lock_bh(&dwc->lock);
	i = dwc->descs_allocated;
	while (dwc->descs_allocated < NR_DESCS_PER_CHANNEL) {
		spin_unlock_bh(&dwc->lock);

		desc = kzalloc(sizeof(struct dw_desc), GFP_KERNEL);
		if (!desc) {
			dev_info(chan2dev(chan),
				"only allocated %d descriptors\n", i);
			spin_lock_bh(&dwc->lock);
			break;
		}

		INIT_LIST_HEAD(&desc->tx_list);
		dma_async_tx_descriptor_init(&desc->txd, chan);
		desc->txd.tx_submit = dwc_tx_submit;
		desc->txd.flags = DMA_CTRL_ACK;
		desc->txd.phys = dma_map_single(chan2parent(chan), &desc->lli,
				sizeof(desc->lli), DMA_TO_DEVICE);
		dwc_desc_put(dwc, desc);

		spin_lock_bh(&dwc->lock);
		i = ++dwc->descs_allocated;
	}

	/* Enable interrupts */
	channel_set_bit(dw, MASK.XFER, dwc->mask);
	channel_set_bit(dw, MASK.BLOCK, dwc->mask);
	channel_set_bit(dw, MASK.ERROR, dwc->mask);

	spin_unlock_bh(&dwc->lock);

	dev_dbg(chan2dev(chan),
		"alloc_chan_resources allocated %d descriptors\n", i);

	return i;
}