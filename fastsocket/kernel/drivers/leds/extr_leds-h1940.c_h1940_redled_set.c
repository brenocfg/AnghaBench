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
 int /*<<< orphan*/  H1940_LATCH_LED_FLASH ; 
 int /*<<< orphan*/  H1940_LATCH_LED_RED ; 
#define  LED_FULL 130 
#define  LED_HALF 129 
#define  LED_OFF 128 
 int /*<<< orphan*/  S3C2410_GPA1 ; 
 int /*<<< orphan*/  h1940_latch_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c2410_gpio_setpin (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void h1940_redled_set(struct led_classdev *led_dev,
			     enum led_brightness value)
{
	switch (value) {
	case LED_HALF:
		h1940_latch_control(0, H1940_LATCH_LED_FLASH);
		s3c2410_gpio_setpin(S3C2410_GPA1, 1);
		break;
	case LED_FULL:
		h1940_latch_control(0, H1940_LATCH_LED_RED);
		s3c2410_gpio_setpin(S3C2410_GPA1, 1);
		break;
	default:
	case LED_OFF:
		h1940_latch_control(H1940_LATCH_LED_FLASH, 0);
		h1940_latch_control(H1940_LATCH_LED_RED, 0);
		s3c2410_gpio_setpin(S3C2410_GPA1, 0);
		break;
	}
}