#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dma_async_tx_descriptor {int flags; void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;int /*<<< orphan*/  cookie; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  private; } ;
struct at_dma_chan {TYPE_2__ chan_common; int /*<<< orphan*/  free_list; int /*<<< orphan*/  completed_cookie; } ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct at_desc {int /*<<< orphan*/  len; TYPE_1__ lli; int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; struct dma_async_tx_descriptor txd; } ;
typedef  int /*<<< orphan*/  (* dma_async_tx_callback ) (void*) ;

/* Variables and functions */
 int DMA_COMPL_DEST_UNMAP_SINGLE ; 
 int DMA_COMPL_SKIP_DEST_UNMAP ; 
 int DMA_COMPL_SKIP_SRC_UNMAP ; 
 int DMA_COMPL_SRC_UNMAP_SINGLE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  chan2dev (TYPE_2__*) ; 
 struct device* chan2parent (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atc_chain_complete(struct at_dma_chan *atchan, struct at_desc *desc)
{
	dma_async_tx_callback		callback;
	void				*param;
	struct dma_async_tx_descriptor	*txd = &desc->txd;

	dev_vdbg(chan2dev(&atchan->chan_common),
		"descriptor %u complete\n", txd->cookie);

	atchan->completed_cookie = txd->cookie;
	callback = txd->callback;
	param = txd->callback_param;

	/* move children to free_list */
	list_splice_init(&desc->tx_list, &atchan->free_list);
	/* move myself to free_list */
	list_move(&desc->desc_node, &atchan->free_list);

	/* unmap dma addresses */
	if (!atchan->chan_common.private) {
		struct device *parent = chan2parent(&atchan->chan_common);
		if (!(txd->flags & DMA_COMPL_SKIP_DEST_UNMAP)) {
			if (txd->flags & DMA_COMPL_DEST_UNMAP_SINGLE)
				dma_unmap_single(parent,
						desc->lli.daddr,
						desc->len, DMA_FROM_DEVICE);
			else
				dma_unmap_page(parent,
						desc->lli.daddr,
						desc->len, DMA_FROM_DEVICE);
		}
		if (!(txd->flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
			if (txd->flags & DMA_COMPL_SRC_UNMAP_SINGLE)
				dma_unmap_single(parent,
						desc->lli.saddr,
						desc->len, DMA_TO_DEVICE);
			else
				dma_unmap_page(parent,
						desc->lli.saddr,
						desc->len, DMA_TO_DEVICE);
		}
	}

	/*
	 * The API requires that no submissions are done from a
	 * callback, so we don't need to drop the lock here
	 */
	if (callback)
		callback(param);

	dma_run_dependencies(txd);
}