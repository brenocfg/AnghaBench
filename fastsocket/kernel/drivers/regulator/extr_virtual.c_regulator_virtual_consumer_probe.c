#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtual_consumer_data {int /*<<< orphan*/  regulator; int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {char* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * attributes ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtual_consumer_data*) ; 
 struct virtual_consumer_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct virtual_consumer_data*) ; 
 int /*<<< orphan*/  regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  regulator_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_virtual_consumer_probe(struct platform_device *pdev)
{
	char *reg_id = pdev->dev.platform_data;
	struct virtual_consumer_data *drvdata;
	int ret, i;

	drvdata = kzalloc(sizeof(struct virtual_consumer_data), GFP_KERNEL);
	if (drvdata == NULL) {
		return -ENOMEM;
	}

	mutex_init(&drvdata->lock);

	drvdata->regulator = regulator_get(&pdev->dev, reg_id);
	if (IS_ERR(drvdata->regulator)) {
		ret = PTR_ERR(drvdata->regulator);
		dev_err(&pdev->dev, "Failed to obtain supply '%s': %d\n",
			reg_id, ret);
		goto err;
	}

	for (i = 0; i < ARRAY_SIZE(attributes); i++) {
		ret = device_create_file(&pdev->dev, attributes[i]);
		if (ret != 0) {
			dev_err(&pdev->dev, "Failed to create attr %d: %d\n",
				i, ret);
			goto err_regulator;
		}
	}

	drvdata->mode = regulator_get_mode(drvdata->regulator);

	platform_set_drvdata(pdev, drvdata);

	return 0;

err_regulator:
	regulator_put(drvdata->regulator);
err:
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		device_remove_file(&pdev->dev, attributes[i]);
	kfree(drvdata);
	return ret;
}