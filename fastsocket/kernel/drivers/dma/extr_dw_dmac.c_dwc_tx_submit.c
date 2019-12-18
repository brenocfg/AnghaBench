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
struct dw_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  active_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;
struct dw_desc {int /*<<< orphan*/  desc_node; TYPE_1__ txd; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_assign_cookie (struct dw_dma_chan*,struct dw_desc*) ; 
 int /*<<< orphan*/  dwc_dostart (struct dw_dma_chan*,struct dw_desc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct dw_dma_chan* to_dw_dma_chan (int /*<<< orphan*/ ) ; 
 struct dw_desc* txd_to_dw_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t dwc_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct dw_desc		*desc = txd_to_dw_desc(tx);
	struct dw_dma_chan	*dwc = to_dw_dma_chan(tx->chan);
	dma_cookie_t		cookie;

	spin_lock_bh(&dwc->lock);
	cookie = dwc_assign_cookie(dwc, desc);

	/*
	 * REVISIT: We should attempt to chain as many descriptors as
	 * possible, perhaps even appending to those already submitted
	 * for DMA. But this is hard to do in a race-free manner.
	 */
	if (list_empty(&dwc->active_list)) {
		dev_vdbg(chan2dev(tx->chan), "tx_submit: started %u\n",
				desc->txd.cookie);
		dwc_dostart(dwc, desc);
		list_add_tail(&desc->desc_node, &dwc->active_list);
	} else {
		dev_vdbg(chan2dev(tx->chan), "tx_submit: queued %u\n",
				desc->txd.cookie);

		list_add_tail(&desc->desc_node, &dwc->queue);
	}

	spin_unlock_bh(&dwc->lock);

	return cookie;
}