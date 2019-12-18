#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  tail; scalar_t__ cb; } ;
struct r8192_priv {int rxringcount; int /*<<< orphan*/  rxbuffersize; int /*<<< orphan*/  pdev; struct sk_buff** rx_buf; TYPE_1__* rx_ring; scalar_t__ rx_idx; int /*<<< orphan*/  rx_ring_dma; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int OWN; int EOR; int /*<<< orphan*/  Length; int /*<<< orphan*/  BufferAddress; } ;
typedef  TYPE_1__ rx_desc_819x_pci ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 short ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short rtl8192_alloc_rx_desc_ring(struct net_device *dev)
{
    struct r8192_priv *priv = ieee80211_priv(dev);
    rx_desc_819x_pci *entry = NULL;
    int i;

    priv->rx_ring = pci_alloc_consistent(priv->pdev,
            sizeof(*priv->rx_ring) * priv->rxringcount, &priv->rx_ring_dma);

    if (!priv->rx_ring || (unsigned long)priv->rx_ring & 0xFF) {
        RT_TRACE(COMP_ERR,"Cannot allocate RX ring\n");
        return -ENOMEM;
    }

    memset(priv->rx_ring, 0, sizeof(*priv->rx_ring) * priv->rxringcount);
    priv->rx_idx = 0;

    for (i = 0; i < priv->rxringcount; i++) {
        struct sk_buff *skb = dev_alloc_skb(priv->rxbuffersize);
        dma_addr_t *mapping;
        entry = &priv->rx_ring[i];
        if (!skb)
            return 0;
        priv->rx_buf[i] = skb;
        mapping = (dma_addr_t *)skb->cb;
        *mapping = pci_map_single(priv->pdev, skb->tail,//skb_tail_pointer(skb),
                priv->rxbuffersize, PCI_DMA_FROMDEVICE);

        entry->BufferAddress = cpu_to_le32(*mapping);

        entry->Length = priv->rxbuffersize;
        entry->OWN = 1;
    }

    entry->EOR = 1;
    return 0;
}