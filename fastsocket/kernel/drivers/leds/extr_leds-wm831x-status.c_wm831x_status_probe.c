#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wm831x_status_pdata {int default_src; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct wm831x_status {int reg_val; int src; TYPE_1__ cdev; int /*<<< orphan*/  brightness; int /*<<< orphan*/  reg; int /*<<< orphan*/  value_lock; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; struct wm831x* wm831x; } ;
struct wm831x_pdata {scalar_t__* status; } ;
struct wm831x {TYPE_2__* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int id; TYPE_4__ dev; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_8__ {struct wm831x_pdata* platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int WM831X_LED_MODE_MASK ; 
 int WM831X_LED_SRC_MASK ; 
 int WM831X_LED_SRC_SHIFT ; 
 int WM831X_STATUS_PRESERVE ; 
 int /*<<< orphan*/  dev_attr_src ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct wm831x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct wm831x_status*) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wm831x_status*) ; 
 struct wm831x_status* kzalloc (int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (struct wm831x_status_pdata*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct wm831x_status_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm831x_status_blink_set ; 
 int /*<<< orphan*/  wm831x_status_set ; 
 int /*<<< orphan*/  wm831x_status_work ; 

__attribute__((used)) static int wm831x_status_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *chip_pdata;
	struct wm831x_status_pdata pdata;
	struct wm831x_status *drvdata;
	struct resource *res;
	int id = pdev->id % ARRAY_SIZE(chip_pdata->status);
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "No I/O resource\n");
		ret = -EINVAL;
		goto err;
	}

	drvdata = kzalloc(sizeof(struct wm831x_status), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;
	dev_set_drvdata(&pdev->dev, drvdata);

	drvdata->wm831x = wm831x;
	drvdata->reg = res->start;

	if (wm831x->dev->platform_data)
		chip_pdata = wm831x->dev->platform_data;
	else
		chip_pdata = NULL;

	memset(&pdata, 0, sizeof(pdata));
	if (chip_pdata && chip_pdata->status[id])
		memcpy(&pdata, chip_pdata->status[id], sizeof(pdata));
	else
		pdata.name = dev_name(&pdev->dev);

	mutex_init(&drvdata->mutex);
	INIT_WORK(&drvdata->work, wm831x_status_work);
	spin_lock_init(&drvdata->value_lock);

	/* We cache the configuration register and read startup values
	 * from it. */
	drvdata->reg_val = wm831x_reg_read(wm831x, drvdata->reg);

	if (drvdata->reg_val & WM831X_LED_MODE_MASK)
		drvdata->brightness = LED_FULL;
	else
		drvdata->brightness = LED_OFF;

	/* Set a default source if configured, otherwise leave the
	 * current hardware setting.
	 */
	if (pdata.default_src == WM831X_STATUS_PRESERVE) {
		drvdata->src = drvdata->reg_val;
		drvdata->src &= WM831X_LED_SRC_MASK;
		drvdata->src >>= WM831X_LED_SRC_SHIFT;
	} else {
		drvdata->src = pdata.default_src - 1;
	}

	drvdata->cdev.name = pdata.name;
	drvdata->cdev.default_trigger = pdata.default_trigger;
	drvdata->cdev.brightness_set = wm831x_status_set;
	drvdata->cdev.blink_set = wm831x_status_blink_set;

	ret = led_classdev_register(wm831x->dev, &drvdata->cdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register LED: %d\n", ret);
		goto err_led;
	}

	ret = device_create_file(drvdata->cdev.dev, &dev_attr_src);
	if (ret != 0)
		dev_err(&pdev->dev,
			"No source control for LED: %d\n", ret);

	return 0;

err_led:
	led_classdev_unregister(&drvdata->cdev);
	kfree(drvdata);
err:
	return ret;
}