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
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct cpmac_priv {int ring_size; int /*<<< orphan*/  dma_ring; TYPE_1__* desc_ring; TYPE_1__* rx_head; int /*<<< orphan*/  pdev; int /*<<< orphan*/  regs; int /*<<< orphan*/  phy; int /*<<< orphan*/  napi; int /*<<< orphan*/  reset_work; } ;
struct cpmac_desc {int dummy; } ;
struct TYPE_2__ {scalar_t__ skb; int /*<<< orphan*/  data_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_MBP ; 
 size_t CPMAC_QUEUES ; 
 int /*<<< orphan*/  CPMAC_RX_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPMAC_SKB_SIZE ; 
 int /*<<< orphan*/  CPMAC_TX_PTR (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpmac_hw_stop (struct net_device*) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int cpmac_stop(struct net_device *dev)
{
	int i;
	struct cpmac_priv *priv = netdev_priv(dev);
	struct resource *mem;

	netif_tx_stop_all_queues(dev);

	cancel_work_sync(&priv->reset_work);
	napi_disable(&priv->napi);
	phy_stop(priv->phy);

	cpmac_hw_stop(dev);

	for (i = 0; i < 8; i++)
		cpmac_write(priv->regs, CPMAC_TX_PTR(i), 0);
	cpmac_write(priv->regs, CPMAC_RX_PTR(0), 0);
	cpmac_write(priv->regs, CPMAC_MBP, 0);

	free_irq(dev->irq, dev);
	iounmap(priv->regs);
	mem = platform_get_resource_byname(priv->pdev, IORESOURCE_MEM, "regs");
	release_mem_region(mem->start, mem->end - mem->start);
	priv->rx_head = &priv->desc_ring[CPMAC_QUEUES];
	for (i = 0; i < priv->ring_size; i++) {
		if (priv->rx_head[i].skb) {
			dma_unmap_single(&dev->dev,
					 priv->rx_head[i].data_mapping,
					 CPMAC_SKB_SIZE,
					 DMA_FROM_DEVICE);
			kfree_skb(priv->rx_head[i].skb);
		}
	}

	dma_free_coherent(&dev->dev, sizeof(struct cpmac_desc) *
			  (CPMAC_QUEUES + priv->ring_size),
			  priv->desc_ring, priv->dma_ring);
	return 0;
}