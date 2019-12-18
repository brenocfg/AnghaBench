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
typedef  scalar_t__ u32 ;
struct dma_chan {int cookie; struct at_dma_slave* private; int /*<<< orphan*/  device; } ;
struct at_dma_slave {scalar_t__ dma_dev; scalar_t__ cfg; } ;
struct at_dma_chan {int descs_allocated; int completed_cookie; int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;
struct TYPE_2__ {scalar_t__ dev; } ;
struct at_dma {TYPE_1__ dma_common; } ;
struct at_desc {int /*<<< orphan*/  desc_node; } ;

/* Variables and functions */
 scalar_t__ ATC_DEFAULT_CFG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CFG ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct at_desc* atc_alloc_descriptor (struct dma_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ atc_chan_is_enabled (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  channel_writel (struct at_dma_chan*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int init_nr_desc_per_channel ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_list ; 
 struct at_dma* to_at_dma (int /*<<< orphan*/ ) ; 
 struct at_dma_chan* to_at_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int atc_alloc_chan_resources(struct dma_chan *chan)
{
	struct at_dma_chan	*atchan = to_at_dma_chan(chan);
	struct at_dma		*atdma = to_at_dma(chan->device);
	struct at_desc		*desc;
	struct at_dma_slave	*atslave;
	int			i;
	u32			cfg;
	LIST_HEAD(tmp_list);

	dev_vdbg(chan2dev(chan), "alloc_chan_resources\n");

	/* ASSERT:  channel is idle */
	if (atc_chan_is_enabled(atchan)) {
		dev_dbg(chan2dev(chan), "DMA channel not idle ?\n");
		return -EIO;
	}

	cfg = ATC_DEFAULT_CFG;

	atslave = chan->private;
	if (atslave) {
		/*
		 * We need controller-specific data to set up slave
		 * transfers.
		 */
		BUG_ON(!atslave->dma_dev || atslave->dma_dev != atdma->dma_common.dev);

		/* if cfg configuration specified take it instad of default */
		if (atslave->cfg)
			cfg = atslave->cfg;
	}

	/* have we already been set up?
	 * reconfigure channel but no need to reallocate descriptors */
	if (!list_empty(&atchan->free_list))
		return atchan->descs_allocated;

	/* Allocate initial pool of descriptors */
	for (i = 0; i < init_nr_desc_per_channel; i++) {
		desc = atc_alloc_descriptor(chan, GFP_KERNEL);
		if (!desc) {
			dev_err(atdma->dma_common.dev,
				"Only %d initial descriptors\n", i);
			break;
		}
		list_add_tail(&desc->desc_node, &tmp_list);
	}

	spin_lock_bh(&atchan->lock);
	atchan->descs_allocated = i;
	list_splice(&tmp_list, &atchan->free_list);
	atchan->completed_cookie = chan->cookie = 1;
	spin_unlock_bh(&atchan->lock);

	/* channel parameters */
	channel_writel(atchan, CFG, cfg);

	dev_dbg(chan2dev(chan),
		"alloc_chan_resources: allocated %d descriptors\n",
		atchan->descs_allocated);

	return atchan->descs_allocated;
}