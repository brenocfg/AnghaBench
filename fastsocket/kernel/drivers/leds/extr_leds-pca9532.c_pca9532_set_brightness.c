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
struct pca9532_led {int /*<<< orphan*/  work; int /*<<< orphan*/  client; int /*<<< orphan*/  state; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_FULL ; 
 int LED_OFF ; 
 int /*<<< orphan*/  PCA9532_OFF ; 
 int /*<<< orphan*/  PCA9532_ON ; 
 int /*<<< orphan*/  PCA9532_PWM0 ; 
 struct pca9532_led* ldev_to_led (struct led_classdev*) ; 
 int pca9532_calcpwm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pca9532_set_brightness(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	int err = 0;
	struct pca9532_led *led = ldev_to_led(led_cdev);

	if (value == LED_OFF)
		led->state = PCA9532_OFF;
	else if (value == LED_FULL)
		led->state = PCA9532_ON;
	else {
		led->state = PCA9532_PWM0; /* Thecus: hardcode one pwm */
		err = pca9532_calcpwm(led->client, 0, 0, value);
		if (err)
			return; /* XXX: led api doesn't allow error code? */
	}
	schedule_work(&led->work);
}