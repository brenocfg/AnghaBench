#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_if_managed {scalar_t__ probe_send_count; int nullfunc_failed; scalar_t__ probe_timeout; TYPE_5__* associated; } ;
struct TYPE_6__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_3__* local; TYPE_1__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  channel; scalar_t__* bssid; } ;
struct TYPE_7__ {int flags; } ;
struct TYPE_8__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int IEEE80211_HW_REPORTS_TX_ACK_STATUS ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* ieee80211_bss_get_ie (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (TYPE_3__*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_send_nullfunc (TYPE_3__*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_probe_req (struct ieee80211_sub_if_data*,scalar_t__*,scalar_t__ const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ max (int,scalar_t__) ; 
 scalar_t__ max_probe_tries ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_wait_ms ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  run_again (struct ieee80211_if_managed*,scalar_t__) ; 

__attribute__((used)) static void ieee80211_mgd_probe_ap_send(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	const u8 *ssid;
	u8 *dst = ifmgd->associated->bssid;
	u8 unicast_limit = max(1, max_probe_tries - 3);

	/*
	 * Try sending broadcast probe requests for the last three
	 * probe requests after the first ones failed since some
	 * buggy APs only support broadcast probe requests.
	 */
	if (ifmgd->probe_send_count >= unicast_limit)
		dst = NULL;

	/*
	 * When the hardware reports an accurate Tx ACK status, it's
	 * better to send a nullfunc frame instead of a probe request,
	 * as it will kick us off the AP quickly if we aren't associated
	 * anymore. The timeout will be reset if the frame is ACKed by
	 * the AP.
	 */
	ifmgd->probe_send_count++;

	if (sdata->local->hw.flags & IEEE80211_HW_REPORTS_TX_ACK_STATUS) {
		ifmgd->nullfunc_failed = false;
		ieee80211_send_nullfunc(sdata->local, sdata, 0);
	} else {
		int ssid_len;

		rcu_read_lock();
		ssid = ieee80211_bss_get_ie(ifmgd->associated, WLAN_EID_SSID);
		if (WARN_ON_ONCE(ssid == NULL))
			ssid_len = 0;
		else
			ssid_len = ssid[1];

		ieee80211_send_probe_req(sdata, dst, ssid + 2, ssid_len, NULL,
					 0, (u32) -1, true, 0,
					 ifmgd->associated->channel, false);
		rcu_read_unlock();
	}

	ifmgd->probe_timeout = jiffies + msecs_to_jiffies(probe_wait_ms);
	run_again(ifmgd, ifmgd->probe_timeout);
	if (sdata->local->hw.flags & IEEE80211_HW_REPORTS_TX_ACK_STATUS)
		ieee80211_flush_queues(sdata->local, sdata);
}