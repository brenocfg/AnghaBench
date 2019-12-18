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
struct sk_buff {scalar_t__ cb; } ;
struct r8192_priv {int rxringcount; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rxbuffersize; struct sk_buff** rx_buf; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8192_free_rx_ring(struct net_device *dev)
{
    struct r8192_priv *priv = ieee80211_priv(dev);
    int i;

    for (i = 0; i < priv->rxringcount; i++) {
        struct sk_buff *skb = priv->rx_buf[i];
        if (!skb)
            continue;

        pci_unmap_single(priv->pdev,
                *((dma_addr_t *)skb->cb),
                priv->rxbuffersize, PCI_DMA_FROMDEVICE);
        kfree_skb(skb);
    }

    pci_free_consistent(priv->pdev, sizeof(*priv->rx_ring) * priv->rxringcount,
            priv->rx_ring, priv->rx_ring_dma);
    priv->rx_ring = NULL;
}