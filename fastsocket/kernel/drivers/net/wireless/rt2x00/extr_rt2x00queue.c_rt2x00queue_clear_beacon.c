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
struct rt2x00_intf {int /*<<< orphan*/  beacon_skb_mutex; int /*<<< orphan*/  beacon; } ;
struct rt2x00_dev {TYPE_1__* ops; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* clear_beacon ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* lib; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00queue_free_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

int rt2x00queue_clear_beacon(struct rt2x00_dev *rt2x00dev,
			     struct ieee80211_vif *vif)
{
	struct rt2x00_intf *intf = vif_to_intf(vif);

	if (unlikely(!intf->beacon))
		return -ENOBUFS;

	mutex_lock(&intf->beacon_skb_mutex);

	/*
	 * Clean up the beacon skb.
	 */
	rt2x00queue_free_skb(intf->beacon);

	/*
	 * Clear beacon (single bssid devices don't need to clear the beacon
	 * since the beacon queue will get stopped anyway).
	 */
	if (rt2x00dev->ops->lib->clear_beacon)
		rt2x00dev->ops->lib->clear_beacon(intf->beacon);

	mutex_unlock(&intf->beacon_skb_mutex);

	return 0;
}