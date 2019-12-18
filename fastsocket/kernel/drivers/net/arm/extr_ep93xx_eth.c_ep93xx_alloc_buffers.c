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
struct ep93xx_priv {TYPE_3__* descs; void** tx_buf; void** rx_buf; int /*<<< orphan*/  descs_dma_addr; } ;
struct ep93xx_descs {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_6__ {TYPE_2__* tdesc; TYPE_1__* rdesc; } ;
struct TYPE_5__ {void* buf_addr; } ;
struct TYPE_4__ {int rdesc1; void* buf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PKT_BUF_SIZE ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 scalar_t__ __get_free_page (int) ; 
 TYPE_3__* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 void* dma_map_single (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ep93xx_free_buffers (struct ep93xx_priv*) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static int ep93xx_alloc_buffers(struct ep93xx_priv *ep)
{
	int i;

	ep->descs = dma_alloc_coherent(NULL, sizeof(struct ep93xx_descs),
				&ep->descs_dma_addr, GFP_KERNEL | GFP_DMA);
	if (ep->descs == NULL)
		return 1;

	for (i = 0; i < RX_QUEUE_ENTRIES; i += 2) {
		void *page;
		dma_addr_t d;

		page = (void *)__get_free_page(GFP_KERNEL | GFP_DMA);
		if (page == NULL)
			goto err;

		d = dma_map_single(NULL, page, PAGE_SIZE, DMA_FROM_DEVICE);
		if (dma_mapping_error(NULL, d)) {
			free_page((unsigned long)page);
			goto err;
		}

		ep->rx_buf[i] = page;
		ep->descs->rdesc[i].buf_addr = d;
		ep->descs->rdesc[i].rdesc1 = (i << 16) | PKT_BUF_SIZE;

		ep->rx_buf[i + 1] = page + PKT_BUF_SIZE;
		ep->descs->rdesc[i + 1].buf_addr = d + PKT_BUF_SIZE;
		ep->descs->rdesc[i + 1].rdesc1 = ((i + 1) << 16) | PKT_BUF_SIZE;
	}

	for (i = 0; i < TX_QUEUE_ENTRIES; i += 2) {
		void *page;
		dma_addr_t d;

		page = (void *)__get_free_page(GFP_KERNEL | GFP_DMA);
		if (page == NULL)
			goto err;

		d = dma_map_single(NULL, page, PAGE_SIZE, DMA_TO_DEVICE);
		if (dma_mapping_error(NULL, d)) {
			free_page((unsigned long)page);
			goto err;
		}

		ep->tx_buf[i] = page;
		ep->descs->tdesc[i].buf_addr = d;

		ep->tx_buf[i + 1] = page + PKT_BUF_SIZE;
		ep->descs->tdesc[i + 1].buf_addr = d + PKT_BUF_SIZE;
	}

	return 0;

err:
	ep93xx_free_buffers(ep);
	return 1;
}