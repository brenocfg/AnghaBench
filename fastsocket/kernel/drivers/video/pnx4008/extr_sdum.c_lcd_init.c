#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  slave_virt_base; } ;

/* Variables and functions */
 scalar_t__ DUM_OUTP_FORMAT1 ; 
 int /*<<< orphan*/  V_LCD_DISPLAY_ON ; 
 int /*<<< orphan*/  V_LCD_STANDBY_OFF ; 
 int /*<<< orphan*/  V_LCD_SYNC_ENABLE ; 
 int /*<<< orphan*/  V_LCD_SYNC_FALL_H ; 
 int /*<<< orphan*/  V_LCD_SYNC_FALL_L ; 
 int /*<<< orphan*/  V_LCD_SYNC_RISE_H ; 
 int /*<<< orphan*/  V_LCD_SYNC_RISE_L ; 
 int /*<<< orphan*/  V_LCD_USE_9BIT_BUS ; 
 TYPE_1__ dum_data ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_reset () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lcd_init(void)
{
	lcd_reset();

	DUM_OUTP_FORMAT1 = 0; /* RGB666 */

	udelay(1);
	iowrite32(V_LCD_STANDBY_OFF, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_USE_9BIT_BUS, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_SYNC_RISE_L, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_SYNC_RISE_H, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_SYNC_FALL_L, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_SYNC_FALL_H, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_SYNC_ENABLE, dum_data.slave_virt_base);
	udelay(1);
	iowrite32(V_LCD_DISPLAY_ON, dum_data.slave_virt_base);
	udelay(1);
}