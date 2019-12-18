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
struct da8xx_fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_DMA_CTRL_REG ; 
 int /*<<< orphan*/  LCD_RASTER_CTRL_REG ; 
 int LCD_RASTER_ENABLE ; 
 int /*<<< orphan*/  lcd_disable_raster (struct da8xx_fb_par*) ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcd_reset(struct da8xx_fb_par *par)
{
	/* Disable the Raster if previously Enabled */
	if (lcdc_read(LCD_RASTER_CTRL_REG) & LCD_RASTER_ENABLE)
		lcd_disable_raster(par);

	/* DMA has to be disabled */
	lcdc_write(0, LCD_DMA_CTRL_REG);
	lcdc_write(0, LCD_RASTER_CTRL_REG);
}