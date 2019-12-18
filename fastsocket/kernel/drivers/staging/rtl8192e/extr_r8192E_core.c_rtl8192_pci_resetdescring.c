#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  TxBuffAddr; } ;
typedef  TYPE_1__ tx_desc_819x_pci ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/  queue; TYPE_1__* desc; } ;
struct r8192_priv {int rxringcount; int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; scalar_t__ rx_idx; TYPE_2__* rx_ring; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int OWN; } ;
typedef  TYPE_2__ rx_desc_819x_pci ;

/* Variables and functions */
 int MAX_TX_QUEUE_COUNT ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8192_pci_resetdescring(struct net_device *dev)
{
    struct r8192_priv *priv = ieee80211_priv(dev);
    int i;

    /* force the rx_idx to the first one */
    if(priv->rx_ring) {
        rx_desc_819x_pci *entry = NULL;
        for (i = 0; i < priv->rxringcount; i++) {
            entry = &priv->rx_ring[i];
            entry->OWN = 1;
        }
        priv->rx_idx = 0;
    }

    /* after reset, release previous pending packet, and force the
     * tx idx to the first one */
    for (i = 0; i < MAX_TX_QUEUE_COUNT; i++) {
        if (priv->tx_ring[i].desc) {
            struct rtl8192_tx_ring *ring = &priv->tx_ring[i];

            while (skb_queue_len(&ring->queue)) {
                tx_desc_819x_pci *entry = &ring->desc[ring->idx];
                struct sk_buff *skb = __skb_dequeue(&ring->queue);

                pci_unmap_single(priv->pdev, le32_to_cpu(entry->TxBuffAddr),
                        skb->len, PCI_DMA_TODEVICE);
                kfree_skb(skb);
                ring->idx = (ring->idx + 1) % ring->entries;
            }
            ring->idx = 0;
        }
    }
}