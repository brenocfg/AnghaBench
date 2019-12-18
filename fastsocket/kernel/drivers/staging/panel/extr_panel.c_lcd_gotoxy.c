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
 int lcd_addr_x ; 
 scalar_t__ lcd_addr_y ; 
 int lcd_bwidth ; 
 int lcd_hwidth ; 
 int /*<<< orphan*/  lcd_write_cmd (int) ; 

__attribute__((used)) static void lcd_gotoxy(void)
{
	lcd_write_cmd(0x80	/* set DDRAM address */
		      | (lcd_addr_y ? lcd_hwidth : 0)
		      /* we force the cursor to stay at the end of the line if it wants to go farther */
		      | ((lcd_addr_x < lcd_bwidth) ? lcd_addr_x &
			 (lcd_hwidth - 1) : lcd_bwidth - 1));
}