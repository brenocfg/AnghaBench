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
struct ieee80211_device {int scanning; int /*<<< orphan*/  scan_sem; int /*<<< orphan*/  softmac_scan_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

void ieee80211_softmac_stop_scan(struct ieee80211_device *ieee)
{
//	unsigned long flags;

	//ieee->sync_scan_hurryup = 1;

	down(&ieee->scan_sem);
//	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->scanning == 1){
		ieee->scanning = 0;
		//del_timer_sync(&ieee->scan_timer);
		cancel_delayed_work(&ieee->softmac_scan_wq);
	}

//	spin_unlock_irqrestore(&ieee->lock, flags);
	up(&ieee->scan_sem);
}