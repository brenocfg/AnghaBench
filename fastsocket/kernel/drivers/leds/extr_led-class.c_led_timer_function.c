#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct led_timer {unsigned long blink_delay_on; unsigned long blink_delay_off; unsigned long blink_brightness; int /*<<< orphan*/  blink_timer; TYPE_1__* cdev; } ;
struct TYPE_3__ {unsigned long brightness; int /*<<< orphan*/  (* brightness_set ) (TYPE_1__*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long LED_OFF ; 
 int /*<<< orphan*/  __led_set_brightness (TYPE_1__*,unsigned long) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static void led_timer_function(unsigned long data)
{
	struct led_timer *led = (struct led_timer *)data;
	unsigned long brightness;
	unsigned long delay;

	if (!led->blink_delay_on || !led->blink_delay_off) {
		led->cdev->brightness_set(led->cdev, LED_OFF);
		return;
	}

	brightness = led->cdev->brightness;
	if (!brightness) {
		/* Time to switch the LED on. */
		brightness = led->blink_brightness;
		delay = led->blink_delay_on;
	} else {
		/* Store the current brightness value to be able
		 * to restore it when the delay_off period is over.
		 */
		led->blink_brightness = brightness;
		brightness = LED_OFF;
		delay = led->blink_delay_off;
	}

	__led_set_brightness(led->cdev, brightness);
	mod_timer(&led->blink_timer, jiffies + msecs_to_jiffies(delay));
}