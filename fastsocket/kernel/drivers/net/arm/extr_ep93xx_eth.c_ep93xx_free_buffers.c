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
struct ep93xx_priv {int /*<<< orphan*/  descs_dma_addr; TYPE_3__* descs; int /*<<< orphan*/ ** tx_buf; int /*<<< orphan*/ ** rx_buf; } ;
struct ep93xx_descs {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {TYPE_2__* tdesc; TYPE_1__* rdesc; } ;
struct TYPE_5__ {scalar_t__ buf_addr; } ;
struct TYPE_4__ {scalar_t__ buf_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void ep93xx_free_buffers(struct ep93xx_priv *ep)
{
	int i;

	for (i = 0; i < RX_QUEUE_ENTRIES; i += 2) {
		dma_addr_t d;

		d = ep->descs->rdesc[i].buf_addr;
		if (d)
			dma_unmap_single(NULL, d, PAGE_SIZE, DMA_FROM_DEVICE);

		if (ep->rx_buf[i] != NULL)
			free_page((unsigned long)ep->rx_buf[i]);
	}

	for (i = 0; i < TX_QUEUE_ENTRIES; i += 2) {
		dma_addr_t d;

		d = ep->descs->tdesc[i].buf_addr;
		if (d)
			dma_unmap_single(NULL, d, PAGE_SIZE, DMA_TO_DEVICE);

		if (ep->tx_buf[i] != NULL)
			free_page((unsigned long)ep->tx_buf[i]);
	}

	dma_free_coherent(NULL, sizeof(struct ep93xx_descs), ep->descs,
							ep->descs_dma_addr);
}