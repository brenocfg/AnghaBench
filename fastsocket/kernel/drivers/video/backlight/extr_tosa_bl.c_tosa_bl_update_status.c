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
struct tosa_bl_data {int dummy; } ;
struct backlight_properties {int brightness; int /*<<< orphan*/  fb_blank; int /*<<< orphan*/  power; } ;
struct backlight_device {int /*<<< orphan*/  dev; struct backlight_properties props; } ;

/* Variables and functions */
 struct tosa_bl_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tosa_bl_set_backlight (struct tosa_bl_data*,int) ; 

__attribute__((used)) static int tosa_bl_update_status(struct backlight_device *dev)
{
	struct backlight_properties *props = &dev->props;
	struct tosa_bl_data *data = dev_get_drvdata(&dev->dev);
	int power = max(props->power, props->fb_blank);
	int brightness = props->brightness;

	if (power)
		brightness = 0;

	tosa_bl_set_backlight(data, brightness);

	return 0;
}