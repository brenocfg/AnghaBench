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
struct TYPE_4__ {struct generic_bl_info* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct generic_bl_info {int limit_mask; char* name; int /*<<< orphan*/  default_intensity; int /*<<< orphan*/  max_intensity; } ;
struct TYPE_3__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  power; int /*<<< orphan*/  max_brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char const*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct generic_bl_info* bl_machinfo ; 
 struct backlight_device* generic_backlight_device ; 
 int /*<<< orphan*/  genericbl_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int genericbl_probe(struct platform_device *pdev)
{
	struct generic_bl_info *machinfo = pdev->dev.platform_data;
	const char *name = "generic-bl";
	struct backlight_device *bd;

	bl_machinfo = machinfo;
	if (!machinfo->limit_mask)
		machinfo->limit_mask = -1;

	if (machinfo->name)
		name = machinfo->name;

	bd = backlight_device_register (name,
		&pdev->dev, NULL, &genericbl_ops);
	if (IS_ERR (bd))
		return PTR_ERR (bd);

	platform_set_drvdata(pdev, bd);

	bd->props.max_brightness = machinfo->max_intensity;
	bd->props.power = FB_BLANK_UNBLANK;
	bd->props.brightness = machinfo->default_intensity;
	backlight_update_status(bd);

	generic_backlight_device = bd;

	printk("Generic Backlight Driver Initialized.\n");
	return 0;
}