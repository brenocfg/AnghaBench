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
struct rt2x00_sta {int wcid; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800_config_wcid (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_config_wcid_attr_bssidx (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_delete_wcid_attr (struct rt2x00_dev*,int) ; 
 int rt2800_find_wcid (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00lib_get_bssidx (struct rt2x00_dev*,struct ieee80211_vif*) ; 
 struct rt2x00_sta* sta_to_rt2x00_sta (struct ieee80211_sta*) ; 

int rt2800_sta_add(struct rt2x00_dev *rt2x00dev, struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta)
{
	int wcid;
	struct rt2x00_sta *sta_priv = sta_to_rt2x00_sta(sta);

	/*
	 * Find next free WCID.
	 */
	wcid = rt2800_find_wcid(rt2x00dev);

	/*
	 * Store selected wcid even if it is invalid so that we can
	 * later decide if the STA is uploaded into the hw.
	 */
	sta_priv->wcid = wcid;

	/*
	 * No space left in the device, however, we can still communicate
	 * with the STA -> No error.
	 */
	if (wcid < 0)
		return 0;

	/*
	 * Clean up WCID attributes and write STA address to the device.
	 */
	rt2800_delete_wcid_attr(rt2x00dev, wcid);
	rt2800_config_wcid(rt2x00dev, sta->addr, wcid);
	rt2800_config_wcid_attr_bssidx(rt2x00dev, wcid,
				       rt2x00lib_get_bssidx(rt2x00dev, vif));
	return 0;
}