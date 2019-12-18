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
struct ieee80211_device {int /*<<< orphan*/  associate_complete_wq; int /*<<< orphan*/  wq; int /*<<< orphan*/  state; int /*<<< orphan*/  associate_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_LINKED ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ieee80211_associate_complete(struct ieee80211_device *ieee)
{
//	int i;
//	struct net_device* dev = ieee->dev;
	del_timer_sync(&ieee->associate_timer);

	ieee->state = IEEE80211_LINKED;
	//ieee->UpdateHalRATRTableHandler(dev, ieee->dot11HTOperationalRateSet);
	queue_work(ieee->wq, &ieee->associate_complete_wq);
}