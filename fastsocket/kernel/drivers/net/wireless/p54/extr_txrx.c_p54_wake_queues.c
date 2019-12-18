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
struct p54_common {scalar_t__ mode; int /*<<< orphan*/  tx_stats_lock; TYPE_2__* hw; TYPE_1__* tx_stats; } ;
struct TYPE_4__ {unsigned int queues; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ limit; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_UNSPECIFIED ; 
 unsigned int P54_QUEUE_DATA ; 
 int /*<<< orphan*/  ieee80211_wake_queue (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  p54_tx_pending (struct p54_common*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void p54_wake_queues(struct p54_common *priv)
{
	unsigned long flags;
	unsigned int i;

	if (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		return ;

	p54_tx_pending(priv);

	spin_lock_irqsave(&priv->tx_stats_lock, flags);
	for (i = 0; i < priv->hw->queues; i++) {
		if (priv->tx_stats[i + P54_QUEUE_DATA].len <
		    priv->tx_stats[i + P54_QUEUE_DATA].limit)
			ieee80211_wake_queue(priv->hw, i);
	}
	spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
}