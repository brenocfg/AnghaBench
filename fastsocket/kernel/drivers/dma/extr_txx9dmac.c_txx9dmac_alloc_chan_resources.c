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
struct txx9dmac_slave {int /*<<< orphan*/  reg_width; scalar_t__ rx_reg; scalar_t__ tx_reg; } ;
struct txx9dmac_desc {int dummy; } ;
struct txx9dmac_chan {int completed; int ccr; int descs_allocated; int /*<<< orphan*/  lock; } ;
struct dma_chan {int cookie; TYPE_1__* device; struct txx9dmac_slave* private; } ;
struct TYPE_2__ {scalar_t__ device_prep_dma_memcpy; } ;

/* Variables and functions */
 int CCR_LE ; 
 int /*<<< orphan*/  CSR ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TXX9_DMA_CCR_EXTRQ ; 
 int TXX9_DMA_CCR_IMMCHN ; 
 int TXX9_DMA_CCR_INTENC ; 
 int TXX9_DMA_CCR_INTENE ; 
 int TXX9_DMA_CCR_SMPCHN ; 
 int TXX9_DMA_CCR_XFSZ (int /*<<< orphan*/ ) ; 
 int TXX9_DMA_CCR_XFSZ_X8 ; 
 int TXX9_DMA_CSR_XFACT ; 
 int TXX9_DMA_INITIAL_DESC_COUNT ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int channel_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct txx9dmac_chan* to_txx9dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  txx9_dma_have_SMPCHN () ; 
 int /*<<< orphan*/  txx9dmac_chan_set_INTENT (struct txx9dmac_chan*) ; 
 int /*<<< orphan*/  txx9dmac_chan_set_SMPCHN (struct txx9dmac_chan*) ; 
 struct txx9dmac_desc* txx9dmac_desc_alloc (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txx9dmac_desc_put (struct txx9dmac_chan*,struct txx9dmac_desc*) ; 

__attribute__((used)) static int txx9dmac_alloc_chan_resources(struct dma_chan *chan)
{
	struct txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	struct txx9dmac_slave *ds = chan->private;
	struct txx9dmac_desc *desc;
	int i;

	dev_vdbg(chan2dev(chan), "alloc_chan_resources\n");

	/* ASSERT:  channel is idle */
	if (channel_readl(dc, CSR) & TXX9_DMA_CSR_XFACT) {
		dev_dbg(chan2dev(chan), "DMA channel not idle?\n");
		return -EIO;
	}

	dc->completed = chan->cookie = 1;

	dc->ccr = TXX9_DMA_CCR_IMMCHN | TXX9_DMA_CCR_INTENE | CCR_LE;
	txx9dmac_chan_set_SMPCHN(dc);
	if (!txx9_dma_have_SMPCHN() || (dc->ccr & TXX9_DMA_CCR_SMPCHN))
		dc->ccr |= TXX9_DMA_CCR_INTENC;
	if (chan->device->device_prep_dma_memcpy) {
		if (ds)
			return -EINVAL;
		dc->ccr |= TXX9_DMA_CCR_XFSZ_X8;
	} else {
		if (!ds ||
		    (ds->tx_reg && ds->rx_reg) || (!ds->tx_reg && !ds->rx_reg))
			return -EINVAL;
		dc->ccr |= TXX9_DMA_CCR_EXTRQ |
			TXX9_DMA_CCR_XFSZ(__ffs(ds->reg_width));
		txx9dmac_chan_set_INTENT(dc);
	}

	spin_lock_bh(&dc->lock);
	i = dc->descs_allocated;
	while (dc->descs_allocated < TXX9_DMA_INITIAL_DESC_COUNT) {
		spin_unlock_bh(&dc->lock);

		desc = txx9dmac_desc_alloc(dc, GFP_KERNEL);
		if (!desc) {
			dev_info(chan2dev(chan),
				"only allocated %d descriptors\n", i);
			spin_lock_bh(&dc->lock);
			break;
		}
		txx9dmac_desc_put(dc, desc);

		spin_lock_bh(&dc->lock);
		i = ++dc->descs_allocated;
	}
	spin_unlock_bh(&dc->lock);

	dev_dbg(chan2dev(chan),
		"alloc_chan_resources allocated %d descriptors\n", i);

	return i;
}