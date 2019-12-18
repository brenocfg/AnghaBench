#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nx_host_rds_ring {int num_desc; int /*<<< orphan*/  dma_size; struct netxen_rx_buffer* rx_buf_arr; } ;
struct netxen_rx_buffer {scalar_t__ state; int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma; } ;
struct netxen_recv_context {struct nx_host_rds_ring* rds_rings; } ;
struct netxen_adapter {int max_rds_rings; int /*<<< orphan*/  pdev; struct netxen_recv_context recv_ctx; } ;

/* Variables and functions */
 scalar_t__ NETXEN_BUFFER_FREE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void netxen_release_rx_buffers(struct netxen_adapter *adapter)
{
	struct netxen_recv_context *recv_ctx;
	struct nx_host_rds_ring *rds_ring;
	struct netxen_rx_buffer *rx_buf;
	int i, ring;

	recv_ctx = &adapter->recv_ctx;
	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];
		for (i = 0; i < rds_ring->num_desc; ++i) {
			rx_buf = &(rds_ring->rx_buf_arr[i]);
			if (rx_buf->state == NETXEN_BUFFER_FREE)
				continue;
			pci_unmap_single(adapter->pdev,
					rx_buf->dma,
					rds_ring->dma_size,
					PCI_DMA_FROMDEVICE);
			if (rx_buf->skb != NULL)
				dev_kfree_skb_any(rx_buf->skb);
		}
	}
}