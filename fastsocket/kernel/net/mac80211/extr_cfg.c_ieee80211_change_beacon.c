#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  beacon; } ;
struct TYPE_4__ {TYPE_1__ ap; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct cfg80211_beacon_data {int dummy; } ;
struct beacon_data {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int ieee80211_assign_beacon (struct ieee80211_sub_if_data*,struct cfg80211_beacon_data*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int) ; 
 struct beacon_data* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_change_beacon(struct wiphy *wiphy, struct net_device *dev,
				   struct cfg80211_beacon_data *params)
{
	struct ieee80211_sub_if_data *sdata;
	struct beacon_data *old;
	int err;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	old = rtnl_dereference(sdata->u.ap.beacon);
	if (!old)
		return -ENOENT;

	err = ieee80211_assign_beacon(sdata, params);
	if (err < 0)
		return err;
	ieee80211_bss_info_change_notify(sdata, err);
	return 0;
}