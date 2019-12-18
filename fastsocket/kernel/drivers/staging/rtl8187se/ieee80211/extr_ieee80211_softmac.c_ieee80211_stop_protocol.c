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
struct ieee80211_device {scalar_t__ iw_mode; scalar_t__ state; int /*<<< orphan*/  start_ibss_wq; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  associate_timer; scalar_t__ proto_started; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  SendDisassociation (struct ieee80211_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_REASON_DISASSOC_STA_HAS_LEFT ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_disassociate (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_scan (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_stop_send_beacons (struct ieee80211_device*) ; 

void ieee80211_stop_protocol(struct ieee80211_device *ieee)
{
	if (!ieee->proto_started)
		return;

	ieee->proto_started = 0;

	ieee80211_stop_send_beacons(ieee);
	if((ieee->iw_mode == IW_MODE_INFRA)&&(ieee->state == IEEE80211_LINKED)) {
		SendDisassociation(ieee,NULL,WLAN_REASON_DISASSOC_STA_HAS_LEFT);
	}
	del_timer_sync(&ieee->associate_timer);
	cancel_delayed_work(&ieee->associate_retry_wq);
	cancel_delayed_work(&ieee->start_ibss_wq);
	ieee80211_stop_scan(ieee);

	ieee80211_disassociate(ieee);
}