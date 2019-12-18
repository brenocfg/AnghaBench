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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  len; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_tx_ring_info {struct sk_buff* skb; int /*<<< orphan*/  hdrlen; int /*<<< orphan*/  mapping; } ;
struct adm8211_tx_hdr {int dummy; } ;
struct adm8211_priv {unsigned int dirty_tx; unsigned int cur_tx; unsigned int tx_ring_size; int /*<<< orphan*/  lock; int /*<<< orphan*/  pdev; struct adm8211_tx_ring_info* tx_buffers; TYPE_1__* tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TDES0_CONTROL_DONE ; 
 int TDES0_CONTROL_OWN ; 
 int TDES0_STATUS_ES ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adm8211_interrupt_tci(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	unsigned int dirty_tx;

	spin_lock(&priv->lock);

	for (dirty_tx = priv->dirty_tx; priv->cur_tx - dirty_tx; dirty_tx++) {
		unsigned int entry = dirty_tx % priv->tx_ring_size;
		u32 status = le32_to_cpu(priv->tx_ring[entry].status);
		struct ieee80211_tx_info *txi;
		struct adm8211_tx_ring_info *info;
		struct sk_buff *skb;

		if (status & TDES0_CONTROL_OWN ||
		    !(status & TDES0_CONTROL_DONE))
			break;

		info = &priv->tx_buffers[entry];
		skb = info->skb;
		txi = IEEE80211_SKB_CB(skb);

		/* TODO: check TDES0_STATUS_TUF and TDES0_STATUS_TRO */

		pci_unmap_single(priv->pdev, info->mapping,
				 info->skb->len, PCI_DMA_TODEVICE);

		ieee80211_tx_info_clear_status(txi);

		skb_pull(skb, sizeof(struct adm8211_tx_hdr));
		memcpy(skb_push(skb, info->hdrlen), skb->cb, info->hdrlen);
		if (!(txi->flags & IEEE80211_TX_CTL_NO_ACK) &&
		    !(status & TDES0_STATUS_ES))
			txi->flags |= IEEE80211_TX_STAT_ACK;

		ieee80211_tx_status_irqsafe(dev, skb);

		info->skb = NULL;
	}

	if (priv->cur_tx - dirty_tx < priv->tx_ring_size - 2)
		ieee80211_wake_queue(dev, 0);

	priv->dirty_tx = dirty_tx;
	spin_unlock(&priv->lock);
}