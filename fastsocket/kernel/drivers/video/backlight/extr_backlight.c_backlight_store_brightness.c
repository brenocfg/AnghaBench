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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned long max_brightness; unsigned long brightness; } ;
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_1__ props; scalar_t__ ops; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_UPDATE_SYSFS ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  backlight_generate_event (struct backlight_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static ssize_t backlight_store_brightness(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc;
	struct backlight_device *bd = to_backlight_device(dev);
	unsigned long brightness;

	rc = strict_strtoul(buf, 0, &brightness);
	if (rc)
		return rc;

	rc = -ENXIO;

	mutex_lock(&bd->ops_lock);
	if (bd->ops) {
		if (brightness > bd->props.max_brightness)
			rc = -EINVAL;
		else {
			pr_debug("backlight: set brightness to %lu\n",
				 brightness);
			bd->props.brightness = brightness;
			backlight_update_status(bd);
			rc = count;
		}
	}
	mutex_unlock(&bd->ops_lock);

	backlight_generate_event(bd, BACKLIGHT_UPDATE_SYSFS);

	return rc;
}