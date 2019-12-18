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
typedef  int u32 ;
struct rt2x00_intf {int enable_beacon; int /*<<< orphan*/  beacon_skb_mutex; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct rt2x00_dev {int intf_beaconing; int /*<<< orphan*/  flags; int /*<<< orphan*/  intf_associated; TYPE_1__ link; int /*<<< orphan*/  bcn; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct ieee80211_hw {struct rt2x00_dev* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  qos; scalar_t__ assoc; scalar_t__ enable_beacon; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  CONFIG_QOS_DISABLED ; 
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00leds_led_assoc (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00lib_config_erp (struct rt2x00_dev*,struct rt2x00_intf*,struct ieee80211_bss_conf*,int) ; 
 int /*<<< orphan*/  rt2x00lib_config_intf (struct rt2x00_dev*,struct rt2x00_intf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_clear_beacon (struct rt2x00_dev*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rt2x00queue_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_update_beacon (struct rt2x00_dev*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

void rt2x00mac_bss_info_changed(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_bss_conf *bss_conf,
				u32 changes)
{
	struct rt2x00_dev *rt2x00dev = hw->priv;
	struct rt2x00_intf *intf = vif_to_intf(vif);

	/*
	 * mac80211 might be calling this function while we are trying
	 * to remove the device or perhaps suspending it.
	 */
	if (!test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		return;

	/*
	 * Update the BSSID.
	 */
	if (changes & BSS_CHANGED_BSSID)
		rt2x00lib_config_intf(rt2x00dev, intf, vif->type, NULL,
				      bss_conf->bssid);

	/*
	 * Update the beacon. This is only required on USB devices. PCI
	 * devices fetch beacons periodically.
	 */
	if (changes & BSS_CHANGED_BEACON && rt2x00_is_usb(rt2x00dev))
		rt2x00queue_update_beacon(rt2x00dev, vif);

	/*
	 * Start/stop beaconing.
	 */
	if (changes & BSS_CHANGED_BEACON_ENABLED) {
		if (!bss_conf->enable_beacon && intf->enable_beacon) {
			rt2x00queue_clear_beacon(rt2x00dev, vif);
			rt2x00dev->intf_beaconing--;
			intf->enable_beacon = false;

			if (rt2x00dev->intf_beaconing == 0) {
				/*
				 * Last beaconing interface disabled
				 * -> stop beacon queue.
				 */
				mutex_lock(&intf->beacon_skb_mutex);
				rt2x00queue_stop_queue(rt2x00dev->bcn);
				mutex_unlock(&intf->beacon_skb_mutex);
			}


		} else if (bss_conf->enable_beacon && !intf->enable_beacon) {
			rt2x00dev->intf_beaconing++;
			intf->enable_beacon = true;

			if (rt2x00dev->intf_beaconing == 1) {
				/*
				 * First beaconing interface enabled
				 * -> start beacon queue.
				 */
				mutex_lock(&intf->beacon_skb_mutex);
				rt2x00queue_start_queue(rt2x00dev->bcn);
				mutex_unlock(&intf->beacon_skb_mutex);
			}
		}
	}

	/*
	 * When the association status has changed we must reset the link
	 * tuner counter. This is because some drivers determine if they
	 * should perform link tuning based on the number of seconds
	 * while associated or not associated.
	 */
	if (changes & BSS_CHANGED_ASSOC) {
		rt2x00dev->link.count = 0;

		if (bss_conf->assoc)
			rt2x00dev->intf_associated++;
		else
			rt2x00dev->intf_associated--;

		rt2x00leds_led_assoc(rt2x00dev, !!rt2x00dev->intf_associated);

		clear_bit(CONFIG_QOS_DISABLED, &rt2x00dev->flags);
	}

	/*
	 * Check for access point which do not support 802.11e . We have to
	 * generate data frames sequence number in S/W for such AP, because
	 * of H/W bug.
	 */
	if (changes & BSS_CHANGED_QOS && !bss_conf->qos)
		set_bit(CONFIG_QOS_DISABLED, &rt2x00dev->flags);

	/*
	 * When the erp information has changed, we should perform
	 * additional configuration steps. For all other changes we are done.
	 */
	if (changes & (BSS_CHANGED_ERP_CTS_PROT | BSS_CHANGED_ERP_PREAMBLE |
		       BSS_CHANGED_ERP_SLOT | BSS_CHANGED_BASIC_RATES |
		       BSS_CHANGED_BEACON_INT | BSS_CHANGED_HT))
		rt2x00lib_config_erp(rt2x00dev, intf, bss_conf, changes);
}