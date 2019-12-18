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
struct omap_backlight {int powermode; } ;
struct backlight_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct omap_backlight* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapbl_blank (struct omap_backlight*,int) ; 

__attribute__((used)) static int omapbl_set_power(struct backlight_device *dev, int state)
{
	struct omap_backlight *bl = dev_get_drvdata(&dev->dev);

	omapbl_blank(bl, state);
	bl->powermode = state;

	return 0;
}