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
 int /*<<< orphan*/  H1940_LATCH_BLUETOOTH_POWER ; 
 int /*<<< orphan*/  LED_HALF ; 
 int /*<<< orphan*/  S3C2410_GPH (int) ; 
 int /*<<< orphan*/  bt_led_trigger ; 
 int /*<<< orphan*/  h1940_latch_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 
 int state ; 

__attribute__((used)) static void h1940bt_enable(int on)
{
	if (on) {
#ifdef CONFIG_LEDS_H1940
		/* flashing Blue */
		led_trigger_event(bt_led_trigger, LED_HALF);
#endif

		/* Power on the chip */
		h1940_latch_control(0, H1940_LATCH_BLUETOOTH_POWER);
		/* Reset the chip */
		mdelay(10);
		s3c2410_gpio_setpin(S3C2410_GPH(1), 1);
		mdelay(10);
		s3c2410_gpio_setpin(S3C2410_GPH(1), 0);

		state = 1;
	}
	else {
#ifdef CONFIG_LEDS_H1940
		led_trigger_event(bt_led_trigger, 0);
#endif

		s3c2410_gpio_setpin(S3C2410_GPH(1), 1);
		mdelay(10);
		s3c2410_gpio_setpin(S3C2410_GPH(1), 0);
		mdelay(10);
		h1940_latch_control(H1940_LATCH_BLUETOOTH_POWER, 0);

		state = 0;
	}
}