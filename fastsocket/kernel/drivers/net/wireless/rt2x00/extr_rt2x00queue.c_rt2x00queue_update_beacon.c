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
struct rt2x00_intf {int /*<<< orphan*/  beacon_skb_mutex; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rt2x00queue_update_beacon_locked (struct rt2x00_dev*,struct ieee80211_vif*) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

int rt2x00queue_update_beacon(struct rt2x00_dev *rt2x00dev,
			      struct ieee80211_vif *vif)
{
	struct rt2x00_intf *intf = vif_to_intf(vif);
	int ret;

	mutex_lock(&intf->beacon_skb_mutex);
	ret = rt2x00queue_update_beacon_locked(rt2x00dev, vif);
	mutex_unlock(&intf->beacon_skb_mutex);

	return ret;
}