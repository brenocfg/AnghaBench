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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ieee80211_if_managed {TYPE_4__* assoc_data; TYPE_3__* auth_data; struct cfg80211_bss* associated; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; TYPE_1__ u; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_bss {int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {struct cfg80211_bss* bss; } ;
struct TYPE_7__ {struct cfg80211_bss* bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_MGD_MTX (struct ieee80211_if_managed*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int* ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_build_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

struct sk_buff *ieee80211_ap_probereq_get(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct cfg80211_bss *cbss;
	struct sk_buff *skb;
	const u8 *ssid;
	int ssid_len;

	if (WARN_ON(sdata->vif.type != NL80211_IFTYPE_STATION))
		return NULL;

	ASSERT_MGD_MTX(ifmgd);

	if (ifmgd->associated)
		cbss = ifmgd->associated;
	else if (ifmgd->auth_data)
		cbss = ifmgd->auth_data->bss;
	else if (ifmgd->assoc_data)
		cbss = ifmgd->assoc_data->bss;
	else
		return NULL;

	rcu_read_lock();
	ssid = ieee80211_bss_get_ie(cbss, WLAN_EID_SSID);
	if (WARN_ON_ONCE(ssid == NULL))
		ssid_len = 0;
	else
		ssid_len = ssid[1];

	skb = ieee80211_build_probe_req(sdata, cbss->bssid,
					(u32) -1, cbss->channel,
					ssid + 2, ssid_len,
					NULL, 0, true);
	rcu_read_unlock();

	return skb;
}