#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {int dummy; } ;
struct sk_buff {int len; scalar_t__ priority; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_10__ {int /*<<< orphan*/ * remote_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  sta; } ;
struct TYPE_12__ {TYPE_5__ mgd; TYPE_4__ wds; TYPE_3__ vlan; } ;
struct TYPE_8__ {int type; } ;
struct ieee80211_sub_if_data {TYPE_6__ u; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct TYPE_7__ {scalar_t__ queues; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_AP_VLAN 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  WLAN_STA_WME ; 
 scalar_t__ cfg80211_classify8021d (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_downgrade_queue (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/  const*) ; 
 struct sta_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

u16 ieee80211_select_queue(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta = NULL;
	const u8 *ra = NULL;
	bool qos = false;

	if (local->hw.queues < IEEE80211_NUM_ACS || skb->len < 6) {
		skb->priority = 0; /* required for correct WPA/11i MIC */
		return 0;
	}

	rcu_read_lock();
	switch (sdata->vif.type) {
	case NL80211_IFTYPE_AP_VLAN:
		sta = rcu_dereference(sdata->u.vlan.sta);
		if (sta) {
			qos = test_sta_flag(sta, WLAN_STA_WME);
			break;
		}
	case NL80211_IFTYPE_AP:
		ra = skb->data;
		break;
	case NL80211_IFTYPE_WDS:
		ra = sdata->u.wds.remote_addr;
		break;
#ifdef CONFIG_MAC80211_MESH
	case NL80211_IFTYPE_MESH_POINT:
		qos = true;
		break;
#endif
	case NL80211_IFTYPE_STATION:
		ra = sdata->u.mgd.bssid;
		break;
	case NL80211_IFTYPE_ADHOC:
		ra = skb->data;
		break;
	default:
		break;
	}

	if (!sta && ra && !is_multicast_ether_addr(ra)) {
		sta = sta_info_get(sdata, ra);
		if (sta)
			qos = test_sta_flag(sta, WLAN_STA_WME);
	}
	rcu_read_unlock();

	if (!qos) {
		skb->priority = 0; /* required for correct WPA/11i MIC */
		return IEEE80211_AC_BE;
	}

	/* use the data classifier to determine what 802.1d tag the
	 * data frame has */
	skb->priority = cfg80211_classify8021d(skb);

	return ieee80211_downgrade_queue(sdata, skb);
}