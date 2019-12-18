#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {int mask; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; TYPE_1__ chan; struct dw_cyclic_desc* cdesc; } ;
struct dw_dma {int dummy; } ;
struct dw_cyclic_desc {int periods; struct dw_cyclic_desc* desc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  XFER; int /*<<< orphan*/  ERROR; int /*<<< orphan*/  BLOCK; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EN ; 
 TYPE_2__ CLEAR ; 
 int /*<<< orphan*/  DW_DMA_IS_CYCLIC ; 
 int /*<<< orphan*/  chan2dev (TYPE_1__*) ; 
 int /*<<< orphan*/  channel_clear_bit (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int dma_readl (struct dw_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_writel (struct dw_dma*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc_desc_put (struct dw_dma_chan*,struct dw_cyclic_desc) ; 
 int /*<<< orphan*/  kfree (struct dw_cyclic_desc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

void dw_dma_cyclic_free(struct dma_chan *chan)
{
	struct dw_dma_chan	*dwc = to_dw_dma_chan(chan);
	struct dw_dma		*dw = to_dw_dma(dwc->chan.device);
	struct dw_cyclic_desc	*cdesc = dwc->cdesc;
	int			i;

	dev_dbg(chan2dev(&dwc->chan), "cyclic free\n");

	if (!cdesc)
		return;

	spin_lock_bh(&dwc->lock);

	channel_clear_bit(dw, CH_EN, dwc->mask);
	while (dma_readl(dw, CH_EN) & dwc->mask)
		cpu_relax();

	dma_writel(dw, CLEAR.BLOCK, dwc->mask);
	dma_writel(dw, CLEAR.ERROR, dwc->mask);
	dma_writel(dw, CLEAR.XFER, dwc->mask);

	spin_unlock_bh(&dwc->lock);

	for (i = 0; i < cdesc->periods; i++)
		dwc_desc_put(dwc, cdesc->desc[i]);

	kfree(cdesc->desc);
	kfree(cdesc);

	clear_bit(DW_DMA_IS_CYCLIC, &dwc->flags);
}