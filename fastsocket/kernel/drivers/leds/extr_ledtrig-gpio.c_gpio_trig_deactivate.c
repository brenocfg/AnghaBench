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
struct gpio_trig_data {scalar_t__ gpio; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_desired_brightness ; 
 int /*<<< orphan*/  dev_attr_gpio ; 
 int /*<<< orphan*/  dev_attr_inverted ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct led_classdev*) ; 
 int /*<<< orphan*/  gpio_to_irq (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gpio_trig_data*) ; 

__attribute__((used)) static void gpio_trig_deactivate(struct led_classdev *led)
{
	struct gpio_trig_data *gpio_data = led->trigger_data;

	if (gpio_data) {
		device_remove_file(led->dev, &dev_attr_gpio);
		device_remove_file(led->dev, &dev_attr_inverted);
		device_remove_file(led->dev, &dev_attr_desired_brightness);
		flush_work(&gpio_data->work);
		if (gpio_data->gpio != 0)
			free_irq(gpio_to_irq(gpio_data->gpio), led);
		kfree(gpio_data);
	}
}