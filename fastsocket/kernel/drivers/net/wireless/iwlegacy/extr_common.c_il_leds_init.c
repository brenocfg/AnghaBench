#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int max_brightness; int /*<<< orphan*/  name; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; } ;
struct il_priv {int led_registered; TYPE_3__ led; TYPE_2__* pci_dev; TYPE_4__* hw; TYPE_1__* cfg; } ;
struct TYPE_9__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int led_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_TPT_LEDTRIG_FL_CONNECTED ; 
#define  IL_LED_BLINK 130 
#define  IL_LED_DEFAULT 129 
#define  IL_LED_RF_STATE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_create_tpt_led_trigger (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_radio_led_name (TYPE_4__*) ; 
 int /*<<< orphan*/  il_blink ; 
 int /*<<< orphan*/  il_led_blink_set ; 
 int /*<<< orphan*/  il_led_brightness_set ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int led_mode ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

void
il_leds_init(struct il_priv *il)
{
	int mode = led_mode;
	int ret;

	if (mode == IL_LED_DEFAULT)
		mode = il->cfg->led_mode;

	il->led.name =
	    kasprintf(GFP_KERNEL, "%s-led", wiphy_name(il->hw->wiphy));
	il->led.brightness_set = il_led_brightness_set;
	il->led.blink_set = il_led_blink_set;
	il->led.max_brightness = 1;

	switch (mode) {
	case IL_LED_DEFAULT:
		WARN_ON(1);
		break;
	case IL_LED_BLINK:
		il->led.default_trigger =
		    ieee80211_create_tpt_led_trigger(il->hw,
						     IEEE80211_TPT_LEDTRIG_FL_CONNECTED,
						     il_blink,
						     ARRAY_SIZE(il_blink));
		break;
	case IL_LED_RF_STATE:
		il->led.default_trigger = ieee80211_get_radio_led_name(il->hw);
		break;
	}

	ret = led_classdev_register(&il->pci_dev->dev, &il->led);
	if (ret) {
		kfree(il->led.name);
		return;
	}

	il->led_registered = true;
}