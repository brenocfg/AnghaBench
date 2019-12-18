#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct fixed_voltage_config* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int n_voltages; struct fixed_voltage_data* name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; } ;
struct fixed_voltage_data {int enable_high; int is_enabled; TYPE_1__ desc; int /*<<< orphan*/  microvolts; int /*<<< orphan*/  dev; int /*<<< orphan*/  gpio; } ;
struct fixed_voltage_config {int enable_high; int enabled_at_boot; int /*<<< orphan*/  gpio; int /*<<< orphan*/  init_data; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  microvolts; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,struct fixed_voltage_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  fixed_voltage_ops ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fixed_voltage_data*) ; 
 struct fixed_voltage_data* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fixed_voltage_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fixed_voltage_data*) ; 
 int /*<<< orphan*/  regulator_register (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,struct fixed_voltage_data*) ; 

__attribute__((used)) static int regulator_fixed_voltage_probe(struct platform_device *pdev)
{
	struct fixed_voltage_config *config = pdev->dev.platform_data;
	struct fixed_voltage_data *drvdata;
	int ret;

	drvdata = kzalloc(sizeof(struct fixed_voltage_data), GFP_KERNEL);
	if (drvdata == NULL) {
		dev_err(&pdev->dev, "Failed to allocate device data\n");
		ret = -ENOMEM;
		goto err;
	}

	drvdata->desc.name = kstrdup(config->supply_name, GFP_KERNEL);
	if (drvdata->desc.name == NULL) {
		dev_err(&pdev->dev, "Failed to allocate supply name\n");
		ret = -ENOMEM;
		goto err;
	}
	drvdata->desc.type = REGULATOR_VOLTAGE;
	drvdata->desc.owner = THIS_MODULE;
	drvdata->desc.ops = &fixed_voltage_ops;
	drvdata->desc.n_voltages = 1;

	drvdata->microvolts = config->microvolts;
	drvdata->gpio = config->gpio;

	if (gpio_is_valid(config->gpio)) {
		drvdata->enable_high = config->enable_high;

		/* FIXME: Remove below print warning
		 *
		 * config->gpio must be set to -EINVAL by platform code if
		 * GPIO control is not required. However, early adopters
		 * not requiring GPIO control may forget to initialize
		 * config->gpio to -EINVAL. This will cause GPIO 0 to be used
		 * for GPIO control.
		 *
		 * This warning will be removed once there are a couple of users
		 * for this driver.
		 */
		if (!config->gpio)
			dev_warn(&pdev->dev,
				"using GPIO 0 for regulator enable control\n");

		ret = gpio_request(config->gpio, config->supply_name);
		if (ret) {
			dev_err(&pdev->dev,
			   "Could not obtain regulator enable GPIO %d: %d\n",
							config->gpio, ret);
			goto err_name;
		}

		/* set output direction without changing state
		 * to prevent glitch
		 */
		drvdata->is_enabled = config->enabled_at_boot;
		ret = drvdata->is_enabled ?
				config->enable_high : !config->enable_high;

		ret = gpio_direction_output(config->gpio, ret);
		if (ret) {
			dev_err(&pdev->dev,
			   "Could not configure regulator enable GPIO %d direction: %d\n",
							config->gpio, ret);
			goto err_gpio;
		}

	} else {
		/* Regulator without GPIO control is considered
		 * always enabled
		 */
		drvdata->is_enabled = 1;
	}

	drvdata->dev = regulator_register(&drvdata->desc, &pdev->dev,
					  config->init_data, drvdata);
	if (IS_ERR(drvdata->dev)) {
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		goto err_gpio;
	}

	platform_set_drvdata(pdev, drvdata);

	dev_dbg(&pdev->dev, "%s supplying %duV\n", drvdata->desc.name,
		drvdata->microvolts);

	return 0;

err_gpio:
	if (gpio_is_valid(config->gpio))
		gpio_free(config->gpio);
err_name:
	kfree(drvdata->desc.name);
err:
	kfree(drvdata);
	return ret;
}