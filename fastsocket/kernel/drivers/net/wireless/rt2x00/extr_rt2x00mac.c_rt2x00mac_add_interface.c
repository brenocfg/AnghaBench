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
struct rt2x00_intf {struct queue_entry* beacon; int /*<<< orphan*/  beacon_skb_mutex; } ;
struct rt2x00_dev {scalar_t__ packet_filter; int /*<<< orphan*/  intf_sta_count; int /*<<< orphan*/  intf_ap_count; int /*<<< orphan*/  flags; struct data_queue* bcn; } ;
struct queue_entry {int /*<<< orphan*/  flags; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct data_queue {unsigned int limit; struct queue_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  DEVICE_STATE_STARTED ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  ENTRY_BCN_ASSIGNED ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00lib_config_intf (struct rt2x00_dev*,struct rt2x00_intf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

int rt2x00mac_add_interface(struct ieee80211_hw *hw,
			    struct ieee80211_vif *vif)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct rt2x00_intf *intf = vif_to_intf(vif);
	struct data_queue *queue = rt2x00dev->bcn;
	struct queue_entry *entry = NULL;
	unsigned int i;

	/*
	 * Don't allow interfaces to be added
	 * the device has disappeared.
	 */
	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags) ||
	    !test_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags))
		return -ENODEV;

	/*
	 * Loop through all beacon queues to find a free
	 * entry. Since there are as much beacon entries
	 * as the maximum interfaces, this search shouldn't
	 * fail.
	 */
	for (i = 0; i < queue->limit; i++) {
		entry = &queue->entries[i];
		if (!test_and_set_bit(ENTRY_BCN_ASSIGNED, &entry->flags))
			break;
	}

	if (unlikely(i == queue->limit))
		return -ENOBUFS;

	/*
	 * We are now absolutely sure the interface can be created,
	 * increase interface count and start initialization.
	 */

	if (vif->type == NL80211_IFTYPE_AP)
		rt2x00dev->intf_ap_count++;
	else
		rt2x00dev->intf_sta_count++;

	mutex_init(&intf->beacon_skb_mutex);
	intf->beacon = entry;

	/*
	 * The MAC address must be configured after the device
	 * has been initialized. Otherwise the device can reset
	 * the MAC registers.
	 * The BSSID address must only be configured in AP mode,
	 * however we should not send an empty BSSID address for
	 * STA interfaces at this time, since this can cause
	 * invalid behavior in the device.
	 */
	rt2x00lib_config_intf(rt2x00dev, intf, vif->type,
			      vif->addr, NULL);

	/*
	 * Some filters depend on the current working mode. We can force
	 * an update during the next configure_filter() run by mac80211 by
	 * resetting the current packet_filter state.
	 */
	rt2x00dev->packet_filter = 0;

	return 0;
}