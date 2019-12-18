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
struct ipw_rx_queue {TYPE_1__* pool; } ;
struct ipw_priv {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_RX_BUF_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_FREE_BUFFERS ; 
 int RX_QUEUE_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ipw_rx_queue*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_rx_queue_free(struct ipw_priv *priv, struct ipw_rx_queue *rxq)
{
	int i;

	if (!rxq)
		return;

	for (i = 0; i < RX_QUEUE_SIZE + RX_FREE_BUFFERS; i++) {
		if (rxq->pool[i].skb != NULL) {
			pci_unmap_single(priv->pci_dev, rxq->pool[i].dma_addr,
					 IPW_RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
			dev_kfree_skb(rxq->pool[i].skb);
		}
	}

	kfree(rxq);
}