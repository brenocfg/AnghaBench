#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct txx9dmac_slave {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  SAR; int /*<<< orphan*/  DAR; } ;
struct TYPE_5__ {int /*<<< orphan*/  SAR; int /*<<< orphan*/  DAR; } ;
struct dma_async_tx_descriptor {int flags; void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;int /*<<< orphan*/  cookie; } ;
struct txx9dmac_desc {int /*<<< orphan*/  len; TYPE_2__ hwdesc32; TYPE_1__ hwdesc; int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; struct dma_async_tx_descriptor txd; } ;
struct TYPE_7__ {struct txx9dmac_slave* private; } ;
struct txx9dmac_chan {TYPE_3__ chan; int /*<<< orphan*/  free_list; int /*<<< orphan*/  completed; } ;
typedef  int /*<<< orphan*/  (* dma_async_tx_callback ) (void*) ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_COMPL_DEST_UNMAP_SINGLE ; 
 int DMA_COMPL_SKIP_DEST_UNMAP ; 
 int DMA_COMPL_SKIP_SRC_UNMAP ; 
 int DMA_COMPL_SRC_UNMAP_SINGLE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  chan2dev (TYPE_3__*) ; 
 int /*<<< orphan*/  chan2parent (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct txx9dmac_desc*) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dmac64 (struct txx9dmac_chan*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9dmac_sync_desc_for_cpu (struct txx9dmac_chan*,struct txx9dmac_desc*) ; 

__attribute__((used)) static void
txx9dmac_descriptor_complete(struct txx9dmac_chan *dc,
			     struct txx9dmac_desc *desc)
{
	dma_async_tx_callback callback;
	void *param;
	struct dma_async_tx_descriptor *txd = &desc->txd;
	struct txx9dmac_slave *ds = dc->chan.private;

	dev_vdbg(chan2dev(&dc->chan), "descriptor %u %p complete\n",
		 txd->cookie, desc);

	dc->completed = txd->cookie;
	callback = txd->callback;
	param = txd->callback_param;

	txx9dmac_sync_desc_for_cpu(dc, desc);
	list_splice_init(&desc->tx_list, &dc->free_list);
	list_move(&desc->desc_node, &dc->free_list);

	if (!ds) {
		dma_addr_t dmaaddr;
		if (!(txd->flags & DMA_COMPL_SKIP_DEST_UNMAP)) {
			dmaaddr = is_dmac64(dc) ?
				desc->hwdesc.DAR : desc->hwdesc32.DAR;
			if (txd->flags & DMA_COMPL_DEST_UNMAP_SINGLE)
				dma_unmap_single(chan2parent(&dc->chan),
					dmaaddr, desc->len, DMA_FROM_DEVICE);
			else
				dma_unmap_page(chan2parent(&dc->chan),
					dmaaddr, desc->len, DMA_FROM_DEVICE);
		}
		if (!(txd->flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
			dmaaddr = is_dmac64(dc) ?
				desc->hwdesc.SAR : desc->hwdesc32.SAR;
			if (txd->flags & DMA_COMPL_SRC_UNMAP_SINGLE)
				dma_unmap_single(chan2parent(&dc->chan),
					dmaaddr, desc->len, DMA_TO_DEVICE);
			else
				dma_unmap_page(chan2parent(&dc->chan),
					dmaaddr, desc->len, DMA_TO_DEVICE);
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