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
struct urb {int /*<<< orphan*/  status; scalar_t__ context; } ;
struct sk_buff {int dummy; } ;
struct rtl8187b_tx_hdr {int dummy; } ;
struct rtl8187_tx_hdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct rtl8187_priv {int /*<<< orphan*/  work; TYPE_2__ b_tx_status; scalar_t__ is_rtl8187b; TYPE_1__* udev; } ;
struct ieee80211_tx_info {int flags; struct ieee80211_hw** rate_driver_data; } ;
struct ieee80211_hw {struct rtl8187_priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void rtl8187_tx_cb(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *)urb->context;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hw *hw = info->rate_driver_data[0];
	struct rtl8187_priv *priv = hw->priv;

	skb_pull(skb, priv->is_rtl8187b ? sizeof(struct rtl8187b_tx_hdr) :
					  sizeof(struct rtl8187_tx_hdr));
	ieee80211_tx_info_clear_status(info);

	if (!(urb->status) && !(info->flags & IEEE80211_TX_CTL_NO_ACK)) {
		if (priv->is_rtl8187b) {
			skb_queue_tail(&priv->b_tx_status.queue, skb);

			/* queue is "full", discard last items */
			while (skb_queue_len(&priv->b_tx_status.queue) > 5) {
				struct sk_buff *old_skb;

				dev_dbg(&priv->udev->dev,
					"transmit status queue full\n");

				old_skb = skb_dequeue(&priv->b_tx_status.queue);
				ieee80211_tx_status_irqsafe(hw, old_skb);
			}
			return;
		} else {
			info->flags |= IEEE80211_TX_STAT_ACK;
		}
	}
	if (priv->is_rtl8187b)
		ieee80211_tx_status_irqsafe(hw, skb);
	else {
		/* Retry information for the RTI8187 is only available by
		 * reading a register in the device. We are in interrupt mode
		 * here, thus queue the skb and finish on a work queue. */
		skb_queue_tail(&priv->b_tx_status.queue, skb);
		ieee80211_queue_delayed_work(hw, &priv->work, 0);
	}
}