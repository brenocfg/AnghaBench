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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl8180_tx_ring {size_t idx; int entries; struct rtl8180_tx_desc* desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  queue; } ;
struct rtl8180_tx_desc {int /*<<< orphan*/  tx_buf; } ;
struct rtl8180_priv {int /*<<< orphan*/  pdev; struct rtl8180_tx_ring* tx_ring; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,struct rtl8180_tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8180_free_tx_ring(struct ieee80211_hw *dev, unsigned int prio)
{
	struct rtl8180_priv *priv = dev->priv;
	struct rtl8180_tx_ring *ring = &priv->tx_ring[prio];

	while (skb_queue_len(&ring->queue)) {
		struct rtl8180_tx_desc *entry = &ring->desc[ring->idx];
		struct sk_buff *skb = __skb_dequeue(&ring->queue);

		pci_unmap_single(priv->pdev, le32_to_cpu(entry->tx_buf),
				 skb->len, PCI_DMA_TODEVICE);
		kfree_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	}

	pci_free_consistent(priv->pdev, sizeof(*ring->desc)*ring->entries,
			    ring->desc, ring->dma);
	ring->desc = NULL;
}