#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sta_info {struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  recalc_smps; int /*<<< orphan*/  smps_mode; TYPE_1__ vif; } ;
struct TYPE_7__ {scalar_t__ action; int smps_control; } ;
struct TYPE_8__ {TYPE_2__ ht_smps; } ;
struct TYPE_9__ {scalar_t__ category; TYPE_3__ u; } ;
struct TYPE_10__ {TYPE_4__ action; } ;
struct ieee80211_mgmt {TYPE_5__ u; int /*<<< orphan*/  frame_control; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_SMPS_DYNAMIC ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int /*<<< orphan*/  IEEE80211_SMPS_STATIC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WLAN_CATEGORY_HT ; 
 scalar_t__ WLAN_HT_ACTION_SMPS ; 
#define  WLAN_HT_SMPS_CONTROL_DISABLED 130 
#define  WLAN_HT_SMPS_CONTROL_DYNAMIC 129 
#define  WLAN_HT_SMPS_CONTROL_STATIC 128 
 int /*<<< orphan*/  ieee80211_check_pending_bar (struct sta_info*,int /*<<< orphan*/ ,int) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static void ieee80211_frame_acked(struct sta_info *sta, struct sk_buff *skb)
{
	struct ieee80211_mgmt *mgmt = (void *) skb->data;
	struct ieee80211_local *local = sta->local;
	struct ieee80211_sub_if_data *sdata = sta->sdata;

	if (ieee80211_is_data_qos(mgmt->frame_control)) {
		struct ieee80211_hdr *hdr = (void *) skb->data;
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		u16 tid = qc[0] & 0xf;

		ieee80211_check_pending_bar(sta, hdr->addr1, tid);
	}

	if (ieee80211_is_action(mgmt->frame_control) &&
	    mgmt->u.action.category == WLAN_CATEGORY_HT &&
	    mgmt->u.action.u.ht_smps.action == WLAN_HT_ACTION_SMPS &&
	    sdata->vif.type == NL80211_IFTYPE_STATION &&
	    ieee80211_sdata_running(sdata)) {
		/*
		 * This update looks racy, but isn't -- if we come
		 * here we've definitely got a station that we're
		 * talking to, and on a managed interface that can
		 * only be the AP. And the only other place updating
		 * this variable in managed mode is before association.
		 */
		switch (mgmt->u.action.u.ht_smps.smps_control) {
		case WLAN_HT_SMPS_CONTROL_DYNAMIC:
			sdata->smps_mode = IEEE80211_SMPS_DYNAMIC;
			break;
		case WLAN_HT_SMPS_CONTROL_STATIC:
			sdata->smps_mode = IEEE80211_SMPS_STATIC;
			break;
		case WLAN_HT_SMPS_CONTROL_DISABLED:
		default: /* shouldn't happen since we don't send that */
			sdata->smps_mode = IEEE80211_SMPS_OFF;
			break;
		}

		ieee80211_queue_work(&local->hw, &sdata->recalc_smps);
	}
}