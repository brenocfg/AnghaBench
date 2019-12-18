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
struct b43legacy_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_4__ {char const* default_trigger; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct b43legacy_led {int activelow; struct b43legacy_wldev* dev; TYPE_2__ led_dev; int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  b43legacy_led_brightness_set ; 
 int /*<<< orphan*/  b43legacy_led_turn_off (struct b43legacy_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacywarn (int /*<<< orphan*/ ,char*,char const*) ; 
 int led_classdev_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int b43legacy_register_led(struct b43legacy_wldev *dev,
				  struct b43legacy_led *led,
				  const char *name,
				  const char *default_trigger,
				  u8 led_index, bool activelow)
{
	int err;

	b43legacy_led_turn_off(dev, led_index, activelow);
	if (led->dev)
		return -EEXIST;
	if (!default_trigger)
		return -EINVAL;
	led->dev = dev;
	led->index = led_index;
	led->activelow = activelow;
	strncpy(led->name, name, sizeof(led->name));

	led->led_dev.name = led->name;
	led->led_dev.default_trigger = default_trigger;
	led->led_dev.brightness_set = b43legacy_led_brightness_set;

	err = led_classdev_register(dev->dev->dev, &led->led_dev);
	if (err) {
		b43legacywarn(dev->wl, "LEDs: Failed to register %s\n", name);
		led->dev = NULL;
		return err;
	}
	return 0;
}