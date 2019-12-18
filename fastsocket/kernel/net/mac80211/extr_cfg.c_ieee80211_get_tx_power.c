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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct TYPE_7__ {int txpower; } ;
struct TYPE_8__ {TYPE_3__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_4__ vif; } ;
struct TYPE_5__ {int power_level; } ;
struct TYPE_6__ {TYPE_1__ conf; } ;
struct ieee80211_local {TYPE_2__ hw; int /*<<< orphan*/  use_chanctx; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_get_tx_power(struct wiphy *wiphy,
				  struct wireless_dev *wdev,
				  int *dbm)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	if (!local->use_chanctx)
		*dbm = local->hw.conf.power_level;
	else
		*dbm = sdata->vif.bss_conf.txpower;

	return 0;
}