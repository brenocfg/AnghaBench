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
struct smscore_gpio_config {int /*<<< orphan*/  PullUpDown; int /*<<< orphan*/  OutputSlewRate; int /*<<< orphan*/  OutputDriving; int /*<<< orphan*/  InputCharacteristics; int /*<<< orphan*/  Direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMS_GPIO_DIRECTION_OUTPUT ; 
 int /*<<< orphan*/  SMS_GPIO_INPUT_CHARACTERISTICS_NORMAL ; 
 int /*<<< orphan*/  SMS_GPIO_OUTPUT_DRIVING_4mA ; 
 int /*<<< orphan*/  SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS ; 
 int /*<<< orphan*/  SMS_GPIO_PULL_UP_DOWN_NONE ; 

__attribute__((used)) static inline void sms_gpio_assign_11xx_default_led_config(
		struct smscore_gpio_config *pGpioConfig) {
	pGpioConfig->Direction = SMS_GPIO_DIRECTION_OUTPUT;
	pGpioConfig->InputCharacteristics =
		SMS_GPIO_INPUT_CHARACTERISTICS_NORMAL;
	pGpioConfig->OutputDriving = SMS_GPIO_OUTPUT_DRIVING_4mA;
	pGpioConfig->OutputSlewRate = SMS_GPIO_OUTPUT_SLEW_RATE_0_45_V_NS;
	pGpioConfig->PullUpDown = SMS_GPIO_PULL_UP_DOWN_NONE;
}