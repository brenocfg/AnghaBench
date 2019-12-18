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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  cr_panel_off () ; 
 int /*<<< orphan*/  cr_panel_on () ; 

__attribute__((used)) static int cr_lcd_set_power(struct lcd_device *ld, int power)
{
	if (power == FB_BLANK_UNBLANK)
		cr_panel_on();
	if (power == FB_BLANK_POWERDOWN)
		cr_panel_off();

	return 0;
}