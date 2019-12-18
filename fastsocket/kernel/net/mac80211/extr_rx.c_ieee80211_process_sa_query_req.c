#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_12__ {TYPE_3__ mgd; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct TYPE_13__ {int /*<<< orphan*/  trans_id; int /*<<< orphan*/  action; } ;
struct TYPE_14__ {TYPE_5__ sa_query; } ;
struct TYPE_15__ {TYPE_6__ u; int /*<<< orphan*/  category; } ;
struct TYPE_16__ {TYPE_7__ action; } ;
struct ieee80211_mgmt {TYPE_8__ u; int /*<<< orphan*/  frame_control; int /*<<< orphan*/  bssid; int /*<<< orphan*/  sa; int /*<<< orphan*/  da; } ;
struct TYPE_9__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_ACTION ; 
 int /*<<< orphan*/  WLAN_ACTION_SA_QUERY_RESPONSE ; 
 int /*<<< orphan*/  WLAN_CATEGORY_SA_QUERY ; 
 int /*<<< orphan*/  WLAN_SA_QUERY_TR_ID_LEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_mgmt*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void ieee80211_process_sa_query_req(struct ieee80211_sub_if_data *sdata,
					   struct ieee80211_mgmt *mgmt,
					   size_t len)
{
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_mgmt *resp;

	if (!ether_addr_equal(mgmt->da, sdata->vif.addr)) {
		/* Not to own unicast address */
		return;
	}

	if (!ether_addr_equal(mgmt->sa, sdata->u.mgd.bssid) ||
	    !ether_addr_equal(mgmt->bssid, sdata->u.mgd.bssid)) {
		/* Not from the current AP or not associated yet. */
		return;
	}

	if (len < 24 + 1 + sizeof(resp->u.action.u.sa_query)) {
		/* Too short SA Query request frame */
		return;
	}

	skb = dev_alloc_skb(sizeof(*resp) + local->hw.extra_tx_headroom);
	if (skb == NULL)
		return;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	resp = (struct ieee80211_mgmt *) skb_put(skb, 24);
	memset(resp, 0, 24);
	memcpy(resp->da, mgmt->sa, ETH_ALEN);
	memcpy(resp->sa, sdata->vif.addr, ETH_ALEN);
	memcpy(resp->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	resp->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	skb_put(skb, 1 + sizeof(resp->u.action.u.sa_query));
	resp->u.action.category = WLAN_CATEGORY_SA_QUERY;
	resp->u.action.u.sa_query.action = WLAN_ACTION_SA_QUERY_RESPONSE;
	memcpy(resp->u.action.u.sa_query.trans_id,
	       mgmt->u.action.u.sa_query.trans_id,
	       WLAN_SA_QUERY_TR_ID_LEN);

	ieee80211_tx_skb(sdata, skb);
}