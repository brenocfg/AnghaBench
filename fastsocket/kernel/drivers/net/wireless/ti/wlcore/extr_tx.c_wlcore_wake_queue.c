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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  hw; scalar_t__* queue_stop_reasons; } ;
typedef  enum wlcore_queue_stop_reason { ____Placeholder_wlcore_queue_stop_reason } wlcore_queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,scalar_t__*) ; 
 int wlcore_tx_get_mac80211_queue (struct wl12xx_vif*,int /*<<< orphan*/ ) ; 

void wlcore_wake_queue(struct wl1271 *wl, struct wl12xx_vif *wlvif, u8 queue,
		       enum wlcore_queue_stop_reason reason)
{
	unsigned long flags;
	int hwq = wlcore_tx_get_mac80211_queue(wlvif, queue);

	spin_lock_irqsave(&wl->wl_lock, flags);

	/* queue should not be clear for this reason */
	WARN_ON_ONCE(!test_and_clear_bit(reason, &wl->queue_stop_reasons[hwq]));

	if (wl->queue_stop_reasons[hwq])
		goto out;

	ieee80211_wake_queue(wl->hw, hwq);

out:
	spin_unlock_irqrestore(&wl->wl_lock, flags);
}