#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct atmel_pwm_bl_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {scalar_t__ max_brightness; int brightness; int /*<<< orphan*/  power; } ;
struct backlight_device {TYPE_1__ props; } ;
struct atmel_pwm_bl_platform_data {scalar_t__ pwm_compare_max; scalar_t__ pwm_duty_max; scalar_t__ pwm_duty_min; scalar_t__ pwm_frequency; int gpio_on; int on_active_low; int /*<<< orphan*/  pwm_channel; } ;
struct atmel_pwm_bl {int gpio_on; int /*<<< orphan*/  pwmc; struct backlight_device* bldev; struct atmel_pwm_bl_platform_data const* pdata; struct platform_device* pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int atmel_pwm_bl_init_pwm (struct atmel_pwm_bl*) ; 
 int /*<<< orphan*/  atmel_pwm_bl_ops ; 
 int /*<<< orphan*/  atmel_pwm_bl_set_intensity (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char*,TYPE_2__*,struct atmel_pwm_bl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 int gpio_direction_output (int,int) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,char*) ; 
 int /*<<< orphan*/  kfree (struct atmel_pwm_bl*) ; 
 struct atmel_pwm_bl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_pwm_bl*) ; 
 int pwm_channel_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pwm_channel_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_pwm_bl_probe(struct platform_device *pdev)
{
	const struct atmel_pwm_bl_platform_data *pdata;
	struct backlight_device *bldev;
	struct atmel_pwm_bl *pwmbl;
	int retval;

	pwmbl = kzalloc(sizeof(struct atmel_pwm_bl), GFP_KERNEL);
	if (!pwmbl)
		return -ENOMEM;

	pwmbl->pdev = pdev;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		retval = -ENODEV;
		goto err_free_mem;
	}

	if (pdata->pwm_compare_max < pdata->pwm_duty_max ||
			pdata->pwm_duty_min > pdata->pwm_duty_max ||
			pdata->pwm_frequency == 0) {
		retval = -EINVAL;
		goto err_free_mem;
	}

	pwmbl->pdata = pdata;
	pwmbl->gpio_on = pdata->gpio_on;

	retval = pwm_channel_alloc(pdata->pwm_channel, &pwmbl->pwmc);
	if (retval)
		goto err_free_mem;

	if (pwmbl->gpio_on != -1) {
		retval = gpio_request(pwmbl->gpio_on, "gpio_atmel_pwm_bl");
		if (retval) {
			pwmbl->gpio_on = -1;
			goto err_free_pwm;
		}

		/* Turn display off by defatult. */
		retval = gpio_direction_output(pwmbl->gpio_on,
				0 ^ pdata->on_active_low);
		if (retval)
			goto err_free_gpio;
	}

	bldev = backlight_device_register("atmel-pwm-bl",
			&pdev->dev, pwmbl, &atmel_pwm_bl_ops);
	if (IS_ERR(bldev)) {
		retval = PTR_ERR(bldev);
		goto err_free_gpio;
	}

	pwmbl->bldev = bldev;

	platform_set_drvdata(pdev, pwmbl);

	/* Power up the backlight by default at middle intesity. */
	bldev->props.power = FB_BLANK_UNBLANK;
	bldev->props.max_brightness = pdata->pwm_duty_max - pdata->pwm_duty_min;
	bldev->props.brightness = bldev->props.max_brightness / 2;

	retval = atmel_pwm_bl_init_pwm(pwmbl);
	if (retval)
		goto err_free_bl_dev;

	atmel_pwm_bl_set_intensity(bldev);

	return 0;

err_free_bl_dev:
	platform_set_drvdata(pdev, NULL);
	backlight_device_unregister(bldev);
err_free_gpio:
	if (pwmbl->gpio_on != -1)
		gpio_free(pwmbl->gpio_on);
err_free_pwm:
	pwm_channel_free(&pwmbl->pwmc);
err_free_mem:
	kfree(pwmbl);
	return retval;
}