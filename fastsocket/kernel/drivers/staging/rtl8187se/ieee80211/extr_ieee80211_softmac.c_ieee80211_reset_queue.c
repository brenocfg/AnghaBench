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
struct TYPE_2__ {int /*<<< orphan*/ * txb; } ;
struct ieee80211_device {int /*<<< orphan*/  lock; scalar_t__ queue_stop; TYPE_1__ tx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_txb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_mgmt_queue (struct ieee80211_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_reset_queue(struct ieee80211_device *ieee)
{
	unsigned long flags;

	spin_lock_irqsave(&ieee->lock,flags);
	init_mgmt_queue(ieee);
	if (ieee->tx_pending.txb){
		ieee80211_txb_free(ieee->tx_pending.txb);
		ieee->tx_pending.txb = NULL;
	}
	ieee->queue_stop = 0;
	spin_unlock_irqrestore(&ieee->lock,flags);

}