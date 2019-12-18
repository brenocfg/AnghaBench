#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timed_gpio_platform_data {int num_gpios; struct timed_gpio* gpios; } ;
struct TYPE_6__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  get_time; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct timed_gpio_data {int /*<<< orphan*/  active_low; int /*<<< orphan*/  gpio; int /*<<< orphan*/  max_timeout; TYPE_2__ dev; int /*<<< orphan*/  lock; TYPE_4__ timer; } ;
struct timed_gpio {int /*<<< orphan*/  active_low; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  gpio; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {struct timed_gpio_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_enable ; 
 int /*<<< orphan*/  gpio_get_time ; 
 int /*<<< orphan*/  gpio_timer_func ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct timed_gpio_data*) ; 
 struct timed_gpio_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct timed_gpio_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int timed_output_dev_register (TYPE_2__*) ; 
 int /*<<< orphan*/  timed_output_dev_unregister (TYPE_2__*) ; 

__attribute__((used)) static int timed_gpio_probe(struct platform_device *pdev)
{
	struct timed_gpio_platform_data *pdata = pdev->dev.platform_data;
	struct timed_gpio *cur_gpio;
	struct timed_gpio_data *gpio_data, *gpio_dat;
	int i, j, ret = 0;

	if (!pdata)
		return -EBUSY;

	gpio_data = kzalloc(sizeof(struct timed_gpio_data) * pdata->num_gpios,
			GFP_KERNEL);
	if (!gpio_data)
		return -ENOMEM;

	for (i = 0; i < pdata->num_gpios; i++) {
		cur_gpio = &pdata->gpios[i];
		gpio_dat = &gpio_data[i];

		hrtimer_init(&gpio_dat->timer, CLOCK_MONOTONIC,
				HRTIMER_MODE_REL);
		gpio_dat->timer.function = gpio_timer_func;
		spin_lock_init(&gpio_dat->lock);

		gpio_dat->dev.name = cur_gpio->name;
		gpio_dat->dev.get_time = gpio_get_time;
		gpio_dat->dev.enable = gpio_enable;
		ret = timed_output_dev_register(&gpio_dat->dev);
		if (ret < 0) {
			for (j = 0; j < i; j++)
				timed_output_dev_unregister(&gpio_data[i].dev);
			kfree(gpio_data);
			return ret;
		}

		gpio_dat->gpio = cur_gpio->gpio;
		gpio_dat->max_timeout = cur_gpio->max_timeout;
		gpio_dat->active_low = cur_gpio->active_low;
		gpio_direction_output(gpio_dat->gpio, gpio_dat->active_low);
	}

	platform_set_drvdata(pdev, gpio_data);

	return 0;
}