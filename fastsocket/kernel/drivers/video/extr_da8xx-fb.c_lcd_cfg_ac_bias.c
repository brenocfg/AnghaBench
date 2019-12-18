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
typedef  int u32 ;

/* Variables and functions */
 int LCD_AC_BIAS_FREQUENCY (int) ; 
 int LCD_AC_BIAS_TRANSITIONS_PER_INT (int) ; 
 int /*<<< orphan*/  LCD_RASTER_TIMING_2_REG ; 
 int lcdc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lcd_cfg_ac_bias(int period, int transitions_per_int)
{
	u32 reg;

	/* Set the AC Bias Period and Number of Transisitons per Interrupt */
	reg = lcdc_read(LCD_RASTER_TIMING_2_REG) & 0xFFF00000;
	reg |= LCD_AC_BIAS_FREQUENCY(period) |
		LCD_AC_BIAS_TRANSITIONS_PER_INT(transitions_per_int);
	lcdc_write(reg, LCD_RASTER_TIMING_2_REG);
}