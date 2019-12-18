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
struct led_classdev {struct gpio_trig_data* trigger_data; } ;
struct gpio_trig_data {unsigned int gpio; int /*<<< orphan*/  work; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int IRQF_SHARED ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct led_classdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct led_classdev*) ; 
 int /*<<< orphan*/  gpio_to_irq (unsigned int) ; 
 int /*<<< orphan*/  gpio_trig_irq ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct led_classdev*) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static ssize_t gpio_trig_gpio_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t n)
{
	struct led_classdev *led = dev_get_drvdata(dev);
	struct gpio_trig_data *gpio_data = led->trigger_data;
	unsigned gpio;
	int ret;

	ret = sscanf(buf, "%u", &gpio);
	if (ret < 1) {
		dev_err(dev, "couldn't read gpio number\n");
		flush_work(&gpio_data->work);
		return -EINVAL;
	}

	if (gpio_data->gpio == gpio)
		return n;

	if (!gpio) {
		if (gpio_data->gpio != 0)
			free_irq(gpio_to_irq(gpio_data->gpio), led);
		gpio_data->gpio = 0;
		return n;
	}

	ret = request_irq(gpio_to_irq(gpio), gpio_trig_irq,
			IRQF_SHARED | IRQF_TRIGGER_RISING
			| IRQF_TRIGGER_FALLING, "ledtrig-gpio", led);
	if (ret) {
		dev_err(dev, "request_irq failed with error %d\n", ret);
	} else {
		if (gpio_data->gpio != 0)
			free_irq(gpio_to_irq(gpio_data->gpio), led);
		gpio_data->gpio = gpio;
	}

	return ret ? ret : n;
}