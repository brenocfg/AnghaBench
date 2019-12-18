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
struct plat_lcd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sony_lcd_init () ; 
 int /*<<< orphan*/  sony_lcd_off () ; 

__attribute__((used)) static void hx4700_lcd_set_power(struct plat_lcd_data *pd, unsigned int power)
{
	if (power)
		sony_lcd_init();
	else
		sony_lcd_off();
}