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
 int EIO ; 
 int /*<<< orphan*/  ENABLE_VAUX3_DEDICATED ; 
 int /*<<< orphan*/  ENABLE_VAUX3_DEV_GRP ; 
 int /*<<< orphan*/  ENABLE_VPLL2_DEDICATED ; 
 int /*<<< orphan*/  ENABLE_VPLL2_DEV_GRP ; 
 int /*<<< orphan*/  LCD_PANEL_BACKLIGHT_GPIO ; 
 int /*<<< orphan*/  LCD_PANEL_ENABLE_GPIO ; 
 int /*<<< orphan*/  PM_RECEIVER ; 
 int /*<<< orphan*/  TWL4030_VAUX3_DEDICATED ; 
 int /*<<< orphan*/  TWL4030_VAUX3_DEV_GRP ; 
 int /*<<< orphan*/  TWL4030_VPLL2_DEDICATED ; 
 int /*<<< orphan*/  TWL4030_VPLL2_DEV_GRP ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 scalar_t__ t2_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ldp_panel_enable(struct lcd_panel *panel)
{
	if (0 != t2_out(PM_RECEIVER, ENABLE_VPLL2_DEDICATED,
			TWL4030_VPLL2_DEDICATED))
		return -EIO;
	if (0 != t2_out(PM_RECEIVER, ENABLE_VPLL2_DEV_GRP,
			TWL4030_VPLL2_DEV_GRP))
		return -EIO;

	gpio_direction_output(LCD_PANEL_ENABLE_GPIO, 1);
	gpio_direction_output(LCD_PANEL_BACKLIGHT_GPIO, 1);

	if (0 != t2_out(PM_RECEIVER, ENABLE_VAUX3_DEDICATED,
				TWL4030_VAUX3_DEDICATED))
		return -EIO;
	if (0 != t2_out(PM_RECEIVER, ENABLE_VAUX3_DEV_GRP,
				TWL4030_VAUX3_DEV_GRP))
		return -EIO;

	return 0;
}