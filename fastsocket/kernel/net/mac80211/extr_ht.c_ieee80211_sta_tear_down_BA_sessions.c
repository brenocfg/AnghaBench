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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
typedef  enum ieee80211_agg_stop_reason { ____Placeholder_ieee80211_agg_stop_reason } ieee80211_agg_stop_reason ;

/* Variables and functions */
 int AGG_STOP_DESTROY_STA ; 
 int AGG_STOP_PEER_REQUEST ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  WLAN_BACK_RECIPIENT ; 
 int /*<<< orphan*/  WLAN_REASON_QSTA_LEAVE_QBSS ; 
 int /*<<< orphan*/  __ieee80211_stop_rx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ieee80211_stop_tx_ba_session (struct sta_info*,int,int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

void ieee80211_sta_tear_down_BA_sessions(struct sta_info *sta,
					 enum ieee80211_agg_stop_reason reason)
{
	int i;

	cancel_work_sync(&sta->ampdu_mlme.work);

	for (i = 0; i <  IEEE80211_NUM_TIDS; i++) {
		__ieee80211_stop_tx_ba_session(sta, i, reason);
		__ieee80211_stop_rx_ba_session(sta, i, WLAN_BACK_RECIPIENT,
					       WLAN_REASON_QSTA_LEAVE_QBSS,
					       reason != AGG_STOP_DESTROY_STA &&
					       reason != AGG_STOP_PEER_REQUEST);
	}
}