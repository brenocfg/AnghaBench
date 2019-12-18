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
typedef  int u8 ;

/* Variables and functions */
 int LEDEN_LEDAON ; 
 int LEDEN_LEDAPWM ; 
 int /*<<< orphan*/  TWL4030_LED_LEDEN ; 
 int /*<<< orphan*/  TWL4030_MODULE_LED ; 
 int cached_leden ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int twl4030_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_led_set_value(int led, int value)
{
	u8 mask = LEDEN_LEDAON | LEDEN_LEDAPWM;
	int status;

	if (led)
		mask <<= 1;

	mutex_lock(&gpio_lock);
	if (value)
		cached_leden &= ~mask;
	else
		cached_leden |= mask;
	status = twl4030_i2c_write_u8(TWL4030_MODULE_LED, cached_leden,
			TWL4030_LED_LEDEN);
	mutex_unlock(&gpio_lock);
}