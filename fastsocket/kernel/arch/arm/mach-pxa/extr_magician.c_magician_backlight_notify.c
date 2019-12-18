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
 int /*<<< orphan*/  EGPIO_MAGICIAN_BL_POWER ; 
 int /*<<< orphan*/  EGPIO_MAGICIAN_BL_POWER2 ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int magician_backlight_notify(int brightness)
{
	gpio_set_value(EGPIO_MAGICIAN_BL_POWER, brightness);
	if (brightness >= 200) {
		gpio_set_value(EGPIO_MAGICIAN_BL_POWER2, 1);
		return brightness - 72;
	} else {
		gpio_set_value(EGPIO_MAGICIAN_BL_POWER2, 0);
		return brightness;
	}
}