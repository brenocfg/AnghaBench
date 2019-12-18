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
struct TYPE_4__ {char const* name; int /*<<< orphan*/  brightness; } ;
struct rt2x00_led {int /*<<< orphan*/  flags; TYPE_2__ led_dev; } ;
struct rt2x00_dev {TYPE_1__* hw; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  LED_REGISTERED ; 
 int led_classdev_register (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 struct device* wiphy_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00leds_register_led(struct rt2x00_dev *rt2x00dev,
				   struct rt2x00_led *led,
				   const char *name)
{
	struct device *device = wiphy_dev(rt2x00dev->hw->wiphy);
	int retval;

	led->led_dev.name = name;
	led->led_dev.brightness = LED_OFF;

	retval = led_classdev_register(device, &led->led_dev);
	if (retval) {
		rt2x00_err(rt2x00dev, "Failed to register led handler\n");
		return retval;
	}

	led->flags |= LED_REGISTERED;

	return 0;
}