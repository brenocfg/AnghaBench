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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_ring {int count; TYPE_1__* buffer_info; int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct e1000_adapter {struct pci_dev* pdev; struct e1000_ring test_rx_ring; struct e1000_ring test_tx_ring; } ;
struct TYPE_2__ {int length; scalar_t__ skb; scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void e1000_free_desc_rings(struct e1000_adapter *adapter)
{
	struct e1000_ring *tx_ring = &adapter->test_tx_ring;
	struct e1000_ring *rx_ring = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int i;

	if (tx_ring->desc && tx_ring->buffer_info) {
		for (i = 0; i < tx_ring->count; i++) {
			if (tx_ring->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
					tx_ring->buffer_info[i].dma,
					tx_ring->buffer_info[i].length,
					DMA_TO_DEVICE);
			if (tx_ring->buffer_info[i].skb)
				dev_kfree_skb(tx_ring->buffer_info[i].skb);
		}
	}

	if (rx_ring->desc && rx_ring->buffer_info) {
		for (i = 0; i < rx_ring->count; i++) {
			if (rx_ring->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
					rx_ring->buffer_info[i].dma,
					2048, DMA_FROM_DEVICE);
			if (rx_ring->buffer_info[i].skb)
				dev_kfree_skb(rx_ring->buffer_info[i].skb);
		}
	}

	if (tx_ring->desc) {
		dma_free_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
				  tx_ring->dma);
		tx_ring->desc = NULL;
	}
	if (rx_ring->desc) {
		dma_free_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
				  rx_ring->dma);
		rx_ring->desc = NULL;
	}

	kfree(tx_ring->buffer_info);
	tx_ring->buffer_info = NULL;
	kfree(rx_ring->buffer_info);
	rx_ring->buffer_info = NULL;
}