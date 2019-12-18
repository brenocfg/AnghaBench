#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timed_gpio_platform_data {int num_gpios; } ;
struct timed_gpio_data {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct timed_gpio_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct timed_gpio_data*) ; 
 struct timed_gpio_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  timed_output_dev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timed_gpio_remove(struct platform_device *pdev)
{
	struct timed_gpio_platform_data *pdata = pdev->dev.platform_data;
	struct timed_gpio_data *gpio_data = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < pdata->num_gpios; i++)
		timed_output_dev_unregister(&gpio_data[i].dev);

	kfree(gpio_data);

	return 0;
}