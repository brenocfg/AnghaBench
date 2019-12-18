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
typedef  size_t u8 ;
struct wl12xx_vif {scalar_t__* tx_queue_count; int /*<<< orphan*/ * links_map; } ;
struct wl1271 {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; int /*<<< orphan*/ * tx_queue_count; TYPE_2__* links; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_3__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 size_t WL1271_FLAG_FW_TX_BUSY ; 
 size_t WL1271_FLAG_TX_PENDING ; 
 scalar_t__ WL1271_TX_QUEUE_HIGH_WATERMARK ; 
 size_t WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  WLCORE_QUEUE_STOP_REASON_WATERMARK ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,...) ; 
 int wl1271_tx_get_queue (int) ; 
 size_t wl12xx_tx_get_hlid (struct wl1271*,struct wl12xx_vif*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct wl12xx_vif* wl12xx_vif_to_data (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wlcore_is_queue_stopped_by_reason_locked (struct wl1271*,struct wl12xx_vif*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ wlcore_is_queue_stopped_locked (struct wl1271*,struct wl12xx_vif*,int) ; 
 int /*<<< orphan*/  wlcore_stop_queue_locked (struct wl1271*,struct wl12xx_vif*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl1271_op_tx(struct ieee80211_hw *hw,
			 struct ieee80211_tx_control *control,
			 struct sk_buff *skb)
{
	struct wl1271 *wl = hw->priv;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_vif *vif = info->control.vif;
	struct wl12xx_vif *wlvif = NULL;
	unsigned long flags;
	int q, mapping;
	u8 hlid;

	if (!vif) {
		wl1271_debug(DEBUG_TX, "DROP skb with no vif");
		ieee80211_free_txskb(hw, skb);
		return;
	}

	wlvif = wl12xx_vif_to_data(vif);
	mapping = skb_get_queue_mapping(skb);
	q = wl1271_tx_get_queue(mapping);

	hlid = wl12xx_tx_get_hlid(wl, wlvif, skb, control->sta);

	spin_lock_irqsave(&wl->wl_lock, flags);

	/*
	 * drop the packet if the link is invalid or the queue is stopped
	 * for any reason but watermark. Watermark is a "soft"-stop so we
	 * allow these packets through.
	 */
	if (hlid == WL12XX_INVALID_LINK_ID ||
	    (!test_bit(hlid, wlvif->links_map)) ||
	     (wlcore_is_queue_stopped_locked(wl, wlvif, q) &&
	      !wlcore_is_queue_stopped_by_reason_locked(wl, wlvif, q,
			WLCORE_QUEUE_STOP_REASON_WATERMARK))) {
		wl1271_debug(DEBUG_TX, "DROP skb hlid %d q %d", hlid, q);
		ieee80211_free_txskb(hw, skb);
		goto out;
	}

	wl1271_debug(DEBUG_TX, "queue skb hlid %d q %d len %d",
		     hlid, q, skb->len);
	skb_queue_tail(&wl->links[hlid].tx_queue[q], skb);

	wl->tx_queue_count[q]++;
	wlvif->tx_queue_count[q]++;

	/*
	 * The workqueue is slow to process the tx_queue and we need stop
	 * the queue here, otherwise the queue will get too long.
	 */
	if (wlvif->tx_queue_count[q] >= WL1271_TX_QUEUE_HIGH_WATERMARK &&
	    !wlcore_is_queue_stopped_by_reason_locked(wl, wlvif, q,
					WLCORE_QUEUE_STOP_REASON_WATERMARK)) {
		wl1271_debug(DEBUG_TX, "op_tx: stopping queues for q %d", q);
		wlcore_stop_queue_locked(wl, wlvif, q,
					 WLCORE_QUEUE_STOP_REASON_WATERMARK);
	}

	/*
	 * The chip specific setup must run before the first TX packet -
	 * before that, the tx_work will not be initialized!
	 */

	if (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags) &&
	    !test_bit(WL1271_FLAG_TX_PENDING, &wl->flags))
		ieee80211_queue_work(wl->hw, &wl->tx_work);

out:
	spin_unlock_irqrestore(&wl->wl_lock, flags);
}