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
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 scalar_t__ OMAP3430_REV_ES1_0 ; 
 int /*<<< orphan*/  PM_RECEIVER ; 
 int /*<<< orphan*/  TWL4030_VPLL2_DEDICATED ; 
 int /*<<< orphan*/  TWL4030_VPLL2_DEV_GRP ; 
 int /*<<< orphan*/  backlight_gpio ; 
 int /*<<< orphan*/  enable_gpio ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ omap_rev () ; 
 int /*<<< orphan*/  t2_out (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdp2430_panel_disable(struct lcd_panel *panel)
{
	gpio_set_value(enable_gpio, 0);
	gpio_set_value(backlight_gpio, 0);
	if (omap_rev() > OMAP3430_REV_ES1_0) {
		t2_out(PM_RECEIVER, 0x0, TWL4030_VPLL2_DEDICATED);
		t2_out(PM_RECEIVER, 0x0, TWL4030_VPLL2_DEV_GRP);
		msleep(4);
	}
}