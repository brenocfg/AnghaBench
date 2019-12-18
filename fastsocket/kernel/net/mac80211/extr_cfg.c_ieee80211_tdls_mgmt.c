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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int flags; } ;
struct sk_buff {int priority; } ;
struct net_device {int dummy; } ;
struct ieee80211_tdls_lnkie {int dummy; } ;
struct ieee80211_tdls_data {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  bssid; int /*<<< orphan*/  associated; } ;
struct TYPE_8__ {TYPE_3__ mgd; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/ * addr; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; TYPE_2__ vif; struct ieee80211_local* local; } ;
struct ieee80211_mgmt {int dummy; } ;
struct TYPE_5__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  IEEE80211_AC_BK ; 
 int /*<<< orphan*/  IEEE80211_AC_VI ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
#define  WLAN_PUB_ACTION_TDLS_DISCOVER_RES 133 
#define  WLAN_TDLS_DISCOVERY_REQUEST 132 
#define  WLAN_TDLS_SETUP_CONFIRM 131 
#define  WLAN_TDLS_SETUP_REQUEST 130 
#define  WLAN_TDLS_SETUP_RESPONSE 129 
#define  WLAN_TDLS_TEARDOWN 128 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int ieee80211_prep_tdls_direct (struct wiphy*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ieee80211_prep_tdls_encap_data (struct wiphy*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ieee80211_subif_start_xmit (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_tdls_add_link_ie (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_skb (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 scalar_t__ max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_tdls_mgmt(struct wiphy *wiphy, struct net_device *dev,
			       u8 *peer, u8 action_code, u8 dialog_token,
			       u16 status_code, const u8 *extra_ies,
			       size_t extra_ies_len)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb = NULL;
	bool send_direct;
	int ret;

	if (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		return -ENOTSUPP;

	/* make sure we are in managed mode, and associated */
	if (sdata->vif.type != NL80211_IFTYPE_STATION ||
	    !sdata->u.mgd.associated)
		return -EINVAL;

	tdls_dbg(sdata, "TDLS mgmt action %d peer %pM\n",
		 action_code, peer);

	skb = dev_alloc_skb(local->hw.extra_tx_headroom +
			    max(sizeof(struct ieee80211_mgmt),
				sizeof(struct ieee80211_tdls_data)) +
			    50 + /* supported rates */
			    7 + /* ext capab */
			    extra_ies_len +
			    sizeof(struct ieee80211_tdls_lnkie));
	if (!skb)
		return -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_RESPONSE:
	case WLAN_TDLS_SETUP_CONFIRM:
	case WLAN_TDLS_TEARDOWN:
	case WLAN_TDLS_DISCOVERY_REQUEST:
		ret = ieee80211_prep_tdls_encap_data(wiphy, dev, peer,
						     action_code, dialog_token,
						     status_code, skb);
		send_direct = false;
		break;
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		ret = ieee80211_prep_tdls_direct(wiphy, dev, peer, action_code,
						 dialog_token, status_code,
						 skb);
		send_direct = true;
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (ret < 0)
		goto fail;

	if (extra_ies_len)
		memcpy(skb_put(skb, extra_ies_len), extra_ies, extra_ies_len);

	/* the TDLS link IE is always added last */
	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_CONFIRM:
	case WLAN_TDLS_TEARDOWN:
	case WLAN_TDLS_DISCOVERY_REQUEST:
		/* we are the initiator */
		ieee80211_tdls_add_link_ie(skb, sdata->vif.addr, peer,
					   sdata->u.mgd.bssid);
		break;
	case WLAN_TDLS_SETUP_RESPONSE:
	case WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		/* we are the responder */
		ieee80211_tdls_add_link_ie(skb, peer, sdata->vif.addr,
					   sdata->u.mgd.bssid);
		break;
	default:
		ret = -ENOTSUPP;
		goto fail;
	}

	if (send_direct) {
		ieee80211_tx_skb(sdata, skb);
		return 0;
	}

	/*
	 * According to 802.11z: Setup req/resp are sent in AC_BK, otherwise
	 * we should default to AC_VI.
	 */
	switch (action_code) {
	case WLAN_TDLS_SETUP_REQUEST:
	case WLAN_TDLS_SETUP_RESPONSE:
		skb_set_queue_mapping(skb, IEEE80211_AC_BK);
		skb->priority = 2;
		break;
	default:
		skb_set_queue_mapping(skb, IEEE80211_AC_VI);
		skb->priority = 5;
		break;
	}

	/* disable bottom halves when entering the Tx path */
	local_bh_disable();
	ret = ieee80211_subif_start_xmit(skb, dev);
	local_bh_enable();

	return ret;

fail:
	dev_kfree_skb(skb);
	return ret;
}