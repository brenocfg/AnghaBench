#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sta_info {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  reason_code; int /*<<< orphan*/  params; } ;
struct TYPE_6__ {TYPE_1__ delba; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ action; } ;
struct ieee80211_mgmt {TYPE_4__ u; int /*<<< orphan*/  sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_STOP_PEER_REQUEST ; 
 int IEEE80211_DELBA_PARAM_INITIATOR_MASK ; 
 int IEEE80211_DELBA_PARAM_TID_MASK ; 
 int WLAN_BACK_INITIATOR ; 
 int /*<<< orphan*/  __ieee80211_stop_rx_ba_session (struct sta_info*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ieee80211_stop_tx_ba_session (struct sta_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_dbg_ratelimited (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void ieee80211_process_delba(struct ieee80211_sub_if_data *sdata,
			     struct sta_info *sta,
			     struct ieee80211_mgmt *mgmt, size_t len)
{
	u16 tid, params;
	u16 initiator;

	params = le16_to_cpu(mgmt->u.action.u.delba.params);
	tid = (params & IEEE80211_DELBA_PARAM_TID_MASK) >> 12;
	initiator = (params & IEEE80211_DELBA_PARAM_INITIATOR_MASK) >> 11;

	ht_dbg_ratelimited(sdata, "delba from %pM (%s) tid %d reason code %d\n",
			   mgmt->sa, initiator ? "initiator" : "recipient",
			   tid,
			   le16_to_cpu(mgmt->u.action.u.delba.reason_code));

	if (initiator == WLAN_BACK_INITIATOR)
		__ieee80211_stop_rx_ba_session(sta, tid, WLAN_BACK_INITIATOR, 0,
					       true);
	else
		__ieee80211_stop_tx_ba_session(sta, tid, AGG_STOP_PEER_REQUEST);
}