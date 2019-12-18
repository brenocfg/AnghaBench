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
struct rt2x00_sta {scalar_t__ wcid; } ;
struct rt2x00_dev {TYPE_2__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int (* sta_remove ) (struct rt2x00_dev*,scalar_t__) ;} ;

/* Variables and functions */
 struct rt2x00_sta* sta_to_rt2x00_sta (struct ieee80211_sta*) ; 
 int stub1 (struct rt2x00_dev*,scalar_t__) ; 

int rt2x00mac_sta_remove(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			 struct ieee80211_sta *sta)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct rt2x00_sta *sta_priv = sta_to_rt2x00_sta(sta);

	/*
	 * If we never sent the STA to the device no need to clean it up.
	 */
	if (sta_priv->wcid < 0)
		return 0;

	return rt2x00dev->ops->lib->sta_remove(rt2x00dev, sta_priv->wcid);
}