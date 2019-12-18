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
struct led_classdev {int /*<<< orphan*/  dev; struct gpio_trig_data* trigger_data; } ;
struct gpio_trig_data {int /*<<< orphan*/  work; struct led_classdev* led; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_desired_brightness ; 
 int /*<<< orphan*/  dev_attr_gpio ; 
 int /*<<< orphan*/  dev_attr_inverted ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_trig_work ; 
 int /*<<< orphan*/  kfree (struct gpio_trig_data*) ; 
 struct gpio_trig_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpio_trig_activate(struct led_classdev *led)
{
	struct gpio_trig_data *gpio_data;
	int ret;

	gpio_data = kzalloc(sizeof(*gpio_data), GFP_KERNEL);
	if (!gpio_data)
		return;

	ret = device_create_file(led->dev, &dev_attr_gpio);
	if (ret)
		goto err_gpio;

	ret = device_create_file(led->dev, &dev_attr_inverted);
	if (ret)
		goto err_inverted;

	ret = device_create_file(led->dev, &dev_attr_desired_brightness);
	if (ret)
		goto err_brightness;

	gpio_data->led = led;
	led->trigger_data = gpio_data;
	INIT_WORK(&gpio_data->work, gpio_trig_work);

	return;

err_brightness:
	device_remove_file(led->dev, &dev_attr_inverted);

err_inverted:
	device_remove_file(led->dev, &dev_attr_gpio);

err_gpio:
	kfree(gpio_data);
}