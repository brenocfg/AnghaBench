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
struct platform_device {int dummy; } ;
struct omap_backlight {int dummy; } ;
struct backlight_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 struct omap_backlight* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct omap_backlight*) ; 
 struct backlight_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int omapbl_remove(struct platform_device *pdev)
{
	struct backlight_device *dev = platform_get_drvdata(pdev);
	struct omap_backlight *bl = dev_get_drvdata(&dev->dev);

	backlight_device_unregister(dev);
	kfree(bl);

	return 0;
}