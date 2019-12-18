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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct b43_wldev {TYPE_2__* wl; } ;
typedef  int /*<<< orphan*/  name ;
typedef  enum b43_led_behaviour { ____Placeholder_b43_led_behaviour } b43_led_behaviour ;
struct TYPE_3__ {int /*<<< orphan*/  led_assoc; int /*<<< orphan*/  led_radio; int /*<<< orphan*/  led_rx; int /*<<< orphan*/  led_tx; } ;
struct TYPE_4__ {TYPE_1__ leds; struct ieee80211_hw* hw; } ;

/* Variables and functions */
#define  B43_LED_ACTIVITY 139 
#define  B43_LED_APTRANSFER 138 
#define  B43_LED_ASSOC 137 
#define  B43_LED_INACTIVE 136 
 int /*<<< orphan*/  B43_LED_MAX_NAME_LEN ; 
#define  B43_LED_MODE_BG 135 
#define  B43_LED_OFF 134 
#define  B43_LED_ON 133 
#define  B43_LED_RADIO_A 132 
#define  B43_LED_RADIO_ALL 131 
#define  B43_LED_RADIO_B 130 
#define  B43_LED_TRANSFER 129 
#define  B43_LED_WEIRD 128 
 int /*<<< orphan*/  b43_register_led (struct b43_wldev*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43warn (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_get_assoc_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_radio_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_rx_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_get_tx_led_name (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_map_led(struct b43_wldev *dev,
			u8 led_index,
			enum b43_led_behaviour behaviour,
			bool activelow)
{
	struct ieee80211_hw *hw = dev->wl->hw;
	char name[B43_LED_MAX_NAME_LEN + 1];

	/* Map the b43 specific LED behaviour value to the
	 * generic LED triggers. */
	switch (behaviour) {
	case B43_LED_INACTIVE:
	case B43_LED_OFF:
	case B43_LED_ON:
		break;
	case B43_LED_ACTIVITY:
	case B43_LED_TRANSFER:
	case B43_LED_APTRANSFER:
		snprintf(name, sizeof(name),
			 "b43-%s::tx", wiphy_name(hw->wiphy));
		b43_register_led(dev, &dev->wl->leds.led_tx, name,
				 ieee80211_get_tx_led_name(hw),
				 led_index, activelow);
		snprintf(name, sizeof(name),
			 "b43-%s::rx", wiphy_name(hw->wiphy));
		b43_register_led(dev, &dev->wl->leds.led_rx, name,
				 ieee80211_get_rx_led_name(hw),
				 led_index, activelow);
		break;
	case B43_LED_RADIO_ALL:
	case B43_LED_RADIO_A:
	case B43_LED_RADIO_B:
	case B43_LED_MODE_BG:
		snprintf(name, sizeof(name),
			 "b43-%s::radio", wiphy_name(hw->wiphy));
		b43_register_led(dev, &dev->wl->leds.led_radio, name,
				 ieee80211_get_radio_led_name(hw),
				 led_index, activelow);
		break;
	case B43_LED_WEIRD:
	case B43_LED_ASSOC:
		snprintf(name, sizeof(name),
			 "b43-%s::assoc", wiphy_name(hw->wiphy));
		b43_register_led(dev, &dev->wl->leds.led_assoc, name,
				 ieee80211_get_assoc_led_name(hw),
				 led_index, activelow);
		break;
	default:
		b43warn(dev->wl, "LEDs: Unknown behaviour 0x%02X\n",
			behaviour);
		break;
	}
}