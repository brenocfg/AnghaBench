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
struct rt2x00_intf {int /*<<< orphan*/  delayed_flags; } ;
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAYED_UPDATE_BEACON ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  rt2x00queue_update_beacon (struct rt2x00_dev*,struct ieee80211_vif*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rt2x00_intf* vif_to_intf (struct ieee80211_vif*) ; 

__attribute__((used)) static void rt2x00lib_intf_scheduled_iter(void *data, u8 *mac,
					  struct ieee80211_vif *vif)
{
	struct rt2x00_dev *rt2x00dev = data;
	struct rt2x00_intf *intf = vif_to_intf(vif);

	/*
	 * It is possible the radio was disabled while the work had been
	 * scheduled. If that happens we should return here immediately,
	 * note that in the spinlock protected area above the delayed_flags
	 * have been cleared correctly.
	 */
	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return;

	if (test_and_clear_bit(DELAYED_UPDATE_BEACON, &intf->delayed_flags))
		rt2x00queue_update_beacon(rt2x00dev, vif);
}