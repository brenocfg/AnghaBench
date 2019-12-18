#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int* bssid; } ;
struct TYPE_10__ {TYPE_2__ mgd; } ;
struct TYPE_8__ {int* addr; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; } ;
struct TYPE_11__ {int action_code; int dialog_token; void* capability; } ;
struct TYPE_12__ {TYPE_4__ tdls_discover_resp; } ;
struct TYPE_13__ {TYPE_5__ u; int /*<<< orphan*/  category; } ;
struct TYPE_14__ {TYPE_6__ action; } ;
struct ieee80211_mgmt {TYPE_7__ u; void* frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_CATEGORY_PUBLIC ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 128 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ieee80211_add_ext_srates_ie (struct ieee80211_sub_if_data*,struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  ieee80211_add_srates_ie (struct ieee80211_sub_if_data*,struct sk_buff*,int,int) ; 
 int ieee80211_get_sdata_band (struct ieee80211_sub_if_data*) ; 
 int ieee80211_get_tdls_sta_capab (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_ext_capab (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_mgmt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int
ieee80211_prep_tdls_direct(struct wiphy *wiphy, struct net_device *dev,
			   u8 *peer, u8 action_code, u8 dialog_token,
			   u16 status_code, struct sk_buff *skb)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	enum ieee80211_band band = ieee80211_get_sdata_band(sdata);
	struct ieee80211_mgmt *mgmt;

	mgmt = (void *)skb_put(skb, 24);
	memset(mgmt, 0, 24);
	memcpy(mgmt->da, peer, ETH_ALEN);
	memcpy(mgmt->sa, sdata->vif.addr, ETH_ALEN);
	memcpy(mgmt->bssid, sdata->u.mgd.bssid, ETH_ALEN);

	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	switch (action_code) {
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		skb_put(skb, 1 + sizeof(mgmt->u.action.u.tdls_discover_resp));
		mgmt->u.action.category = WLAN_CATEGORY_PUBLIC;
		mgmt->u.action.u.tdls_discover_resp.action_code =
			WLAN_PUB_ACTION_TDLS_DISCOVER_RES;
		mgmt->u.action.u.tdls_discover_resp.dialog_token =
			dialog_token;
		mgmt->u.action.u.tdls_discover_resp.capability =
			cpu_to_le16(ieee80211_get_tdls_sta_capab(sdata));

		ieee80211_add_srates_ie(sdata, skb, false, band);
		ieee80211_add_ext_srates_ie(sdata, skb, false, band);
		ieee80211_tdls_add_ext_capab(skb);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}