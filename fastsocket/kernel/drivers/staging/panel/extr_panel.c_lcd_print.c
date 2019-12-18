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
 scalar_t__ lcd_bwidth ; 
 char* lcd_char_conv ; 
 int /*<<< orphan*/  lcd_gotoxy () ; 
 int /*<<< orphan*/  lcd_write_data (char) ; 

__attribute__((used)) static void lcd_print(char c)
{
	if (lcd_addr_x < lcd_bwidth) {
		if (lcd_char_conv != NULL)
			c = lcd_char_conv[(unsigned char)c];
		lcd_write_data(c);
		lcd_addr_x++;
	}
	/* prevents the cursor from wrapping onto the next line */
	if (lcd_addr_x == lcd_bwidth)
		lcd_gotoxy();
}