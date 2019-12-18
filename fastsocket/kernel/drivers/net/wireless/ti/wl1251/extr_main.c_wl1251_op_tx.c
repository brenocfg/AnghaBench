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
struct wl1251 {int tx_queue_stopped; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  tx_work; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_control {int dummy; } ;
struct ieee80211_hw {struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 scalar_t__ WL1251_TX_QUEUE_HIGH_WATERMARK ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wl1251_op_tx(struct ieee80211_hw *hw,
			 struct ieee80211_tx_control *control,
			 struct sk_buff *skb)
{
	struct wl1251 *wl = hw->priv;
	unsigned long flags;

	skb_queue_tail(&wl->tx_queue, skb);

	/*
	 * The chip specific setup must run before the first TX packet -
	 * before that, the tx_work will not be initialized!
	 */

	ieee80211_queue_work(wl->hw, &wl->tx_work);

	/*
	 * The workqueue is slow to process the tx_queue and we need stop
	 * the queue here, otherwise the queue will get too long.
	 */
	if (skb_queue_len(&wl->tx_queue) >= WL1251_TX_QUEUE_HIGH_WATERMARK) {
		wl1251_debug(DEBUG_TX, "op_tx: tx_queue full, stop queues");

		spin_lock_irqsave(&wl->wl_lock, flags);
		ieee80211_stop_queues(wl->hw);
		wl->tx_queue_stopped = true;
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	}
}