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
struct TYPE_2__ {int /*<<< orphan*/  cookie; } ;
struct txx9dmac_desc {int /*<<< orphan*/  desc_node; TYPE_1__ txd; } ;
struct txx9dmac_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct txx9dmac_desc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct txx9dmac_chan* to_txx9dmac_chan (int /*<<< orphan*/ ) ; 
 struct txx9dmac_desc* txd_to_txx9dmac_desc (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  txx9dmac_assign_cookie (struct txx9dmac_chan*,struct txx9dmac_desc*) ; 

__attribute__((used)) static dma_cookie_t txx9dmac_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct txx9dmac_desc *desc = txd_to_txx9dmac_desc(tx);
	struct txx9dmac_chan *dc = to_txx9dmac_chan(tx->chan);
	dma_cookie_t cookie;

	spin_lock_bh(&dc->lock);
	cookie = txx9dmac_assign_cookie(dc, desc);

	dev_vdbg(chan2dev(tx->chan), "tx_submit: queued %u %p\n",
		 desc->txd.cookie, desc);

	list_add_tail(&desc->desc_node, &dc->queue);
	spin_unlock_bh(&dc->lock);

	return cookie;
}