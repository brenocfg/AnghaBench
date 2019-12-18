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
typedef  int u8 ;
struct sta_info {scalar_t__ local_pm; } ;

/* Variables and functions */
 int IEEE80211_QOS_CTL_EOSP ; 
 int IEEE80211_QOS_CTL_RSPI ; 
 scalar_t__ NL80211_MESH_POWER_ACTIVE ; 
 int /*<<< orphan*/  WLAN_STA_MPSP_OWNER ; 
 int /*<<< orphan*/  WLAN_STA_MPSP_RECIPIENT ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_frame_deliver (struct sta_info*,int) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

void ieee80211_mpsp_trigger_process(u8 *qc, struct sta_info *sta,
				    bool tx, bool acked)
{
	u8 rspi = qc[1] & (IEEE80211_QOS_CTL_RSPI >> 8);
	u8 eosp = qc[0] & IEEE80211_QOS_CTL_EOSP;

	if (tx) {
		if (rspi && acked)
			set_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);

		if (eosp)
			clear_sta_flag(sta, WLAN_STA_MPSP_OWNER);
		else if (acked &&
			 test_sta_flag(sta, WLAN_STA_PS_STA) &&
			 !test_and_set_sta_flag(sta, WLAN_STA_MPSP_OWNER))
			mps_frame_deliver(sta, -1);
	} else {
		if (eosp)
			clear_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);
		else if (sta->local_pm != NL80211_MESH_POWER_ACTIVE)
			set_sta_flag(sta, WLAN_STA_MPSP_RECIPIENT);

		if (rspi && !test_and_set_sta_flag(sta, WLAN_STA_MPSP_OWNER))
			mps_frame_deliver(sta, -1);
	}
}