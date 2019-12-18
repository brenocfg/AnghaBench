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
 int AMS_DELTA_DEFAULT_CONTRAST ; 
 int /*<<< orphan*/  AMS_DELTA_LATCH2_LCD_NDISP ; 
 int /*<<< orphan*/  AMS_DELTA_LATCH2_LCD_VBLEN ; 
 int /*<<< orphan*/  OMAP_PWL_CLK_ENABLE ; 
 int /*<<< orphan*/  OMAP_PWL_ENABLE ; 
 int /*<<< orphan*/  ams_delta_latch2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ams_delta_panel_enable(struct lcd_panel *panel)
{
	ams_delta_latch2_write(AMS_DELTA_LATCH2_LCD_NDISP,
			AMS_DELTA_LATCH2_LCD_NDISP);
	ams_delta_latch2_write(AMS_DELTA_LATCH2_LCD_VBLEN,
			AMS_DELTA_LATCH2_LCD_VBLEN);

	omap_writeb(1, OMAP_PWL_CLK_ENABLE);
	omap_writeb(AMS_DELTA_DEFAULT_CONTRAST, OMAP_PWL_ENABLE);

	return 0;
}