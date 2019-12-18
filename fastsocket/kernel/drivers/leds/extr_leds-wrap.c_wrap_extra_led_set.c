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
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  WRAP_EXTRA_LED_GPIO ; 
 int /*<<< orphan*/  scx200_gpio_set_high (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scx200_gpio_set_low (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wrap_extra_led_set(struct led_classdev *led_cdev,
		enum led_brightness value)
{
	if (value)
		scx200_gpio_set_low(WRAP_EXTRA_LED_GPIO);
	else
		scx200_gpio_set_high(WRAP_EXTRA_LED_GPIO);
}