#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct led_pwm_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct led_pwm_platform_data {int num_leds; struct led_pwm* leds; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct led_pwm_data {int /*<<< orphan*/  pwm; TYPE_1__ cdev; int /*<<< orphan*/  period; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  active_low; } ;
struct led_pwm {int /*<<< orphan*/  pwm_period_ns; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  active_low; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; int /*<<< orphan*/  pwm_id; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct led_pwm_data*) ; 
 struct led_pwm_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  led_pwm_set ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct led_pwm_data*) ; 
 int /*<<< orphan*/  pwm_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int led_pwm_probe(struct platform_device *pdev)
{
	struct led_pwm_platform_data *pdata = pdev->dev.platform_data;
	struct led_pwm *cur_led;
	struct led_pwm_data *leds_data, *led_dat;
	int i, ret = 0;

	if (!pdata)
		return -EBUSY;

	leds_data = kzalloc(sizeof(struct led_pwm_data) * pdata->num_leds,
				GFP_KERNEL);
	if (!leds_data)
		return -ENOMEM;

	for (i = 0; i < pdata->num_leds; i++) {
		cur_led = &pdata->leds[i];
		led_dat = &leds_data[i];

		led_dat->pwm = pwm_request(cur_led->pwm_id,
				cur_led->name);
		if (IS_ERR(led_dat->pwm)) {
			dev_err(&pdev->dev, "unable to request PWM %d\n",
					cur_led->pwm_id);
			goto err;
		}

		led_dat->cdev.name = cur_led->name;
		led_dat->cdev.default_trigger = cur_led->default_trigger;
		led_dat->active_low = cur_led->active_low;
		led_dat->max_brightness = cur_led->max_brightness;
		led_dat->period = cur_led->pwm_period_ns;
		led_dat->cdev.brightness_set = led_pwm_set;
		led_dat->cdev.brightness = LED_OFF;
		led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;

		ret = led_classdev_register(&pdev->dev, &led_dat->cdev);
		if (ret < 0) {
			pwm_free(led_dat->pwm);
			goto err;
		}
	}

	platform_set_drvdata(pdev, leds_data);

	return 0;

err:
	if (i > 0) {
		for (i = i - 1; i >= 0; i--) {
			led_classdev_unregister(&leds_data[i].cdev);
			pwm_free(leds_data[i].pwm);
		}
	}

	kfree(leds_data);

	return ret;
}