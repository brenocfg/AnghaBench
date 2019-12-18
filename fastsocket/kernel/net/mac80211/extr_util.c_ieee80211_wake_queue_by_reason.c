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
struct ieee80211_local {int /*<<< orphan*/  queue_stop_reason_lock; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum queue_stop_reason { ____Placeholder_queue_stop_reason } queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  __ieee80211_wake_queue (struct ieee80211_hw*,int,int) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_wake_queue_by_reason(struct ieee80211_hw *hw, int queue,
				    enum queue_stop_reason reason)
{
	struct ieee80211_local *local = hw_to_local(hw);
	unsigned long flags;

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	__ieee80211_wake_queue(hw, queue, reason);
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
}