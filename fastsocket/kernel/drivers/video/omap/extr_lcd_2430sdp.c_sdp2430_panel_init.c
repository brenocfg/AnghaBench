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
struct omapfb_device {int dummy; } ;
struct lcd_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDP2430_LCD_PANEL_BACKLIGHT_GPIO ; 
 int /*<<< orphan*/  SDP2430_LCD_PANEL_ENABLE_GPIO ; 
 int /*<<< orphan*/  SDP3430_LCD_PANEL_BACKLIGHT_GPIO ; 
 int /*<<< orphan*/  SDP3430_LCD_PANEL_ENABLE_GPIO ; 
 int /*<<< orphan*/  backlight_gpio ; 
 int /*<<< orphan*/  enable_gpio ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_request (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ machine_is_omap_3430sdp () ; 

__attribute__((used)) static int sdp2430_panel_init(struct lcd_panel *panel,
				struct omapfb_device *fbdev)
{
	if (machine_is_omap_3430sdp()) {
		enable_gpio    = SDP3430_LCD_PANEL_ENABLE_GPIO;
		backlight_gpio = SDP3430_LCD_PANEL_BACKLIGHT_GPIO;
	} else {
		enable_gpio    = SDP2430_LCD_PANEL_ENABLE_GPIO;
		backlight_gpio = SDP2430_LCD_PANEL_BACKLIGHT_GPIO;
	}

	gpio_request(enable_gpio, "LCD enable");	/* LCD panel */
	gpio_request(backlight_gpio, "LCD bl");		/* LCD backlight */
	gpio_direction_output(enable_gpio, 0);
	gpio_direction_output(backlight_gpio, 0);

	return 0;
}