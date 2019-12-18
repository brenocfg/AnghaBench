#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_set_default_key (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ieee80211_config_default_key(struct wiphy *wiphy,
					struct net_device *dev,
					u8 key_idx, bool uni,
					bool multi)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_set_default_key(sdata, key_idx, uni, multi);

	return 0;
}