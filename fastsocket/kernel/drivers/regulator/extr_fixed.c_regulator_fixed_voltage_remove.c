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
struct platform_device {int dummy; } ;
struct TYPE_2__ {struct fixed_voltage_data* name; } ;
struct fixed_voltage_data {TYPE_1__ desc; int /*<<< orphan*/  gpio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fixed_voltage_data*) ; 
 struct fixed_voltage_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_fixed_voltage_remove(struct platform_device *pdev)
{
	struct fixed_voltage_data *drvdata = platform_get_drvdata(pdev);

	regulator_unregister(drvdata->dev);
	if (gpio_is_valid(drvdata->gpio))
		gpio_free(drvdata->gpio);
	kfree(drvdata->desc.name);
	kfree(drvdata);

	return 0;
}