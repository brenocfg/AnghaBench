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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct station_parameters {int sta_flags_set; struct net_device* vlan; } ;
struct sta_info {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  IEEE80211_STA_ASSOC ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTH ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_TDLS_PEER ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_layer2_update (struct sta_info*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rate_control_rate_init (struct sta_info*) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int sta_apply_parameters (struct ieee80211_local*,struct sta_info*,struct station_parameters*) ; 
 struct sta_info* sta_info_alloc (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_free (struct ieee80211_local*,struct sta_info*) ; 
 int sta_info_insert_rcu (struct sta_info*) ; 
 int /*<<< orphan*/  sta_info_pre_move_state (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_add_station(struct wiphy *wiphy, struct net_device *dev,
				 u8 *mac, struct station_parameters *params)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct sta_info *sta;
	struct ieee80211_sub_if_data *sdata;
	int err;
	int layer2_update;

	if (params->vlan) {
		sdata = IEEE80211_DEV_TO_SUB_IF(params->vlan);

		if (sdata->vif.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vif.type != NL80211_IFTYPE_AP)
			return -EINVAL;
	} else
		sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	if (ether_addr_equal(mac, sdata->vif.addr))
		return -EINVAL;

	if (is_multicast_ether_addr(mac))
		return -EINVAL;

	sta = sta_info_alloc(sdata, mac, GFP_KERNEL);
	if (!sta)
		return -ENOMEM;

	/*
	 * defaults -- if userspace wants something else we'll
	 * change it accordingly in sta_apply_parameters()
	 */
	if (!(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER))) {
		sta_info_pre_move_state(sta, IEEE80211_STA_AUTH);
		sta_info_pre_move_state(sta, IEEE80211_STA_ASSOC);
	}

	err = sta_apply_parameters(local, sta, params);
	if (err) {
		sta_info_free(local, sta);
		return err;
	}

	/*
	 * for TDLS, rate control should be initialized only when
	 * rates are known and station is marked authorized
	 */
	if (!test_sta_flag(sta, WLAN_STA_TDLS_PEER))
		rate_control_rate_init(sta);

	layer2_update = sdata->vif.type == NL80211_IFTYPE_AP_VLAN ||
		sdata->vif.type == NL80211_IFTYPE_AP;

	err = sta_info_insert_rcu(sta);
	if (err) {
		rcu_read_unlock();
		return err;
	}

	if (layer2_update)
		ieee80211_send_layer2_update(sta);

	rcu_read_unlock();

	return 0;
}