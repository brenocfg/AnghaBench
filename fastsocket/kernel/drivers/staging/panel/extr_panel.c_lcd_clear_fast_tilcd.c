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
 int /*<<< orphan*/  lcd_gotoxy () ; 
 int lcd_height ; 
 int lcd_hwidth ; 
 int /*<<< orphan*/  pprt ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void lcd_clear_fast_tilcd(void)
{
	int pos;
	lcd_addr_x = lcd_addr_y = 0;
	lcd_gotoxy();

	spin_lock(&pprt_lock);
	for (pos = 0; pos < lcd_height * lcd_hwidth; pos++) {
		/* present the data to the data port */
		w_dtr(pprt, ' ');
		udelay(60);
	}

	spin_unlock(&pprt_lock);

	lcd_addr_x = lcd_addr_y = 0;
	lcd_gotoxy();
}