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
struct ieee80211_local {int /*<<< orphan*/  queue_stop_reason_lock; int /*<<< orphan*/ * queue_stop_reasons; } ;
struct ieee80211_hw {int queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_QUEUE_STOP_REASON_DRIVER ; 
 scalar_t__ WARN_ON (int) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ieee80211_queue_stopped(struct ieee80211_hw *hw, int queue)
{
	struct ieee80211_local *local = hw_to_local(hw);
	unsigned long flags;
	int ret;

	if (WARN_ON(queue >= hw->queues))
		return true;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	ret = test_bit(IEEE80211_QUEUE_STOP_REASON_DRIVER,
		       &local->queue_stop_reasons[queue]);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
	return ret;
}