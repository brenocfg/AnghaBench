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
struct TYPE_5__ {int /*<<< orphan*/  private; } ;
struct dw_dma_chan {TYPE_2__ chan; int /*<<< orphan*/  free_list; int /*<<< orphan*/  completed; } ;
struct TYPE_4__ {int /*<<< orphan*/  sar; int /*<<< orphan*/  dar; } ;
struct dma_async_tx_descriptor {int flags; void* callback_param; int /*<<< orphan*/  (* callback ) (void*) ;int /*<<< orphan*/  cookie; } ;
struct dw_desc {int /*<<< orphan*/  len; TYPE_1__ lli; int /*<<< orphan*/  desc_node; int /*<<< orphan*/  tx_list; struct dma_async_tx_descriptor txd; } ;
struct device {int dummy; } ;
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
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_sync_desc_for_cpu (struct dw_dma_chan*,struct dw_desc*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dwc_descriptor_complete(struct dw_dma_chan *dwc, struct dw_desc *desc)
{
	dma_async_tx_callback		callback;
	void				*param;
	struct dma_async_tx_descriptor	*txd = &desc->txd;

	dev_vdbg(chan2dev(&dwc->chan), "descriptor %u complete\n", txd->cookie);

	dwc->completed = txd->cookie;
	callback = txd->callback;
	param = txd->callback_param;

	dwc_sync_desc_for_cpu(dwc, desc);
	list_splice_init(&desc->tx_list, &dwc->free_list);
	list_move(&desc->desc_node, &dwc->free_list);

	if (!dwc->chan.private) {
		struct device *parent = chan2parent(&dwc->chan);
		if (!(txd->flags & DMA_COMPL_SKIP_DEST_UNMAP)) {
			if (txd->flags & DMA_COMPL_DEST_UNMAP_SINGLE)
				dma_unmap_single(parent, desc->lli.dar,
						desc->len, DMA_FROM_DEVICE);
			else
				dma_unmap_page(parent, desc->lli.dar,
						desc->len, DMA_FROM_DEVICE);
		}
		if (!(txd->flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
			if (txd->flags & DMA_COMPL_SRC_UNMAP_SINGLE)
				dma_unmap_single(parent, desc->lli.sar,
						desc->len, DMA_TO_DEVICE);
			else
				dma_unmap_page(parent, desc->lli.sar,
						desc->len, DMA_TO_DEVICE);
		}
	}

	/*
	 * The API requires that no submissions are done from a
	 * callback, so we don't need to drop the lock here
	 */
	if (callback)
		callback(param);
}