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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct da903x_backlight_data {int id; int /*<<< orphan*/  da903x_dev; scalar_t__ current_brightness; } ;
struct TYPE_3__ {int max_brightness; int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
#define  DA9030_ID_WLED 129 
 int DA9030_MAX_BRIGHTNESS ; 
#define  DA9034_ID_WLED 128 
 int DA9034_MAX_BRIGHTNESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct da903x_backlight_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  da903x_backlight_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct da903x_backlight_data*) ; 
 struct da903x_backlight_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 

__attribute__((used)) static int da903x_backlight_probe(struct platform_device *pdev)
{
	struct da903x_backlight_data *data;
	struct backlight_device *bl;
	int max_brightness;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	switch (pdev->id) {
	case DA9030_ID_WLED:
		max_brightness = DA9030_MAX_BRIGHTNESS;
		break;
	case DA9034_ID_WLED:
		max_brightness = DA9034_MAX_BRIGHTNESS;
		break;
	default:
		dev_err(&pdev->dev, "invalid backlight device ID(%d)\n",
				pdev->id);
		kfree(data);
		return -EINVAL;
	}

	data->id = pdev->id;
	data->da903x_dev = pdev->dev.parent;
	data->current_brightness = 0;

	bl = backlight_device_register(pdev->name, data->da903x_dev,
			data, &da903x_backlight_ops);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		kfree(data);
		return PTR_ERR(bl);
	}

	bl->props.max_brightness = max_brightness;
	bl->props.brightness = max_brightness;

	platform_set_drvdata(pdev, bl);
	backlight_update_status(bl);
	return 0;
}