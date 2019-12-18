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

/* Variables and functions */
 scalar_t__ lcd_addr_x ; 
 scalar_t__ lcd_addr_y ; 
 int /*<<< orphan*/  lcd_write_cmd (int) ; 
 int /*<<< orphan*/  long_sleep (int) ; 

__attribute__((used)) static void lcd_clear_display(void)
{
	lcd_write_cmd(0x01);	/* clear display */
	lcd_addr_x = lcd_addr_y = 0;
	/* we must wait a few milliseconds (15) */
	long_sleep(15);
}