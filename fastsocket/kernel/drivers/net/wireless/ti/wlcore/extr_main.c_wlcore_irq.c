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
struct wl1271 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/ * elp_compl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WL1271_FLAG_FW_TX_BUSY ; 
 int /*<<< orphan*/  WL1271_FLAG_IRQ_RUNNING ; 
 int /*<<< orphan*/  WL1271_FLAG_PENDING_WORK ; 
 int /*<<< orphan*/  WL1271_FLAG_SUSPENDED ; 
 int /*<<< orphan*/  WL1271_FLAG_TX_PENDING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wl1271_tx_total_queue_count (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_queue_recovery_work (struct wl1271*) ; 
 int wlcore_irq_locked (struct wl1271*) ; 

__attribute__((used)) static irqreturn_t wlcore_irq(int irq, void *cookie)
{
	int ret;
	unsigned long flags;
	struct wl1271 *wl = cookie;

	/* complete the ELP completion */
	spin_lock_irqsave(&wl->wl_lock, flags);
	set_bit(WL1271_FLAG_IRQ_RUNNING, &wl->flags);
	if (wl->elp_compl) {
		complete(wl->elp_compl);
		wl->elp_compl = NULL;
	}

	if (test_bit(WL1271_FLAG_SUSPENDED, &wl->flags)) {
		/* don't enqueue a work right now. mark it as pending */
		set_bit(WL1271_FLAG_PENDING_WORK, &wl->flags);
		wl1271_debug(DEBUG_IRQ, "should not enqueue work");
		disable_irq_nosync(wl->irq);
#if 0 /* Not in RHEL */
		pm_wakeup_event(wl->dev, 0);
#endif
		spin_unlock_irqrestore(&wl->wl_lock, flags);
		return IRQ_HANDLED;
	}
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	/* TX might be handled here, avoid redundant work */
	set_bit(WL1271_FLAG_TX_PENDING, &wl->flags);
	cancel_work_sync(&wl->tx_work);

	mutex_lock(&wl->mutex);

	ret = wlcore_irq_locked(wl);
	if (ret)
		wl12xx_queue_recovery_work(wl);

	spin_lock_irqsave(&wl->wl_lock, flags);
	/* In case TX was not handled here, queue TX work */
	clear_bit(WL1271_FLAG_TX_PENDING, &wl->flags);
	if (!test_bit(WL1271_FLAG_FW_TX_BUSY, &wl->flags) &&
	    wl1271_tx_total_queue_count(wl) > 0)
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	spin_unlock_irqrestore(&wl->wl_lock, flags);

	mutex_unlock(&wl->mutex);

	return IRQ_HANDLED;
}