#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {struct wm831x_backlight_pdata* backlight; } ;
struct wm831x_backlight_pdata {scalar_t__ max_uA; int isink; } ;
struct wm831x_backlight_data {int isink_reg; scalar_t__ current_brightness; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct TYPE_7__ {TYPE_3__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_6__ {int max_brightness; int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct TYPE_8__ {struct wm831x_pdata* platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int WM831X_CURRENT_SINK_1 ; 
 int WM831X_CURRENT_SINK_2 ; 
 int /*<<< orphan*/  WM831X_DC4_CONTROL ; 
 int WM831X_DC4_ENA ; 
 int WM831X_DC4_FBSRC ; 
 int /*<<< orphan*/  WM831X_DCDC_ENABLE ; 
 int WM831X_ISINK_MAX_ISEL ; 
 struct backlight_device* backlight_device_register (char*,TYPE_2__*,struct wm831x_backlight_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct wm831x* dev_get_drvdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct wm831x_backlight_data*) ; 
 struct wm831x_backlight_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct backlight_device*) ; 
 int /*<<< orphan*/  wm831x_backlight_ops ; 
 scalar_t__* wm831x_isinkv_values ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int wm831x_backlight_probe(struct platform_device *pdev)
{
	struct wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	struct wm831x_pdata *wm831x_pdata;
	struct wm831x_backlight_pdata *pdata;
	struct wm831x_backlight_data *data;
	struct backlight_device *bl;
	int ret, i, max_isel, isink_reg, dcdc_cfg;

	/* We need platform data */
	if (pdev->dev.parent->platform_data) {
		wm831x_pdata = pdev->dev.parent->platform_data;
		pdata = wm831x_pdata->backlight;
	} else {
		pdata = NULL;
	}

	if (!pdata) {
		dev_err(&pdev->dev, "No platform data supplied\n");
		return -EINVAL;
	}

	/* Figure out the maximum current we can use */
	for (i = 0; i < WM831X_ISINK_MAX_ISEL; i++) {
		if (wm831x_isinkv_values[i] > pdata->max_uA)
			break;
	}

	if (i == 0) {
		dev_err(&pdev->dev, "Invalid max_uA: %duA\n", pdata->max_uA);
		return -EINVAL;
	}
	max_isel = i - 1;

	if (pdata->max_uA != wm831x_isinkv_values[max_isel])
		dev_warn(&pdev->dev,
			 "Maximum current is %duA not %duA as requested\n",
			 wm831x_isinkv_values[max_isel], pdata->max_uA);

	switch (pdata->isink) {
	case 1:
		isink_reg = WM831X_CURRENT_SINK_1;
		dcdc_cfg = 0;
		break;
	case 2:
		isink_reg = WM831X_CURRENT_SINK_2;
		dcdc_cfg = WM831X_DC4_FBSRC;
		break;
	default:
		dev_err(&pdev->dev, "Invalid ISINK %d\n", pdata->isink);
		return -EINVAL;
	}

	/* Configure the ISINK to use for feedback */
	ret = wm831x_reg_unlock(wm831x);
	if (ret < 0)
		return ret;

	ret = wm831x_set_bits(wm831x, WM831X_DC4_CONTROL, WM831X_DC4_FBSRC,
			      dcdc_cfg);

	wm831x_reg_lock(wm831x);
	if (ret < 0)
		return ret;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	data->wm831x = wm831x;
	data->current_brightness = 0;
	data->isink_reg = isink_reg;

	bl = backlight_device_register("wm831x", &pdev->dev,
			data, &wm831x_backlight_ops);
	if (IS_ERR(bl)) {
		dev_err(&pdev->dev, "failed to register backlight\n");
		kfree(data);
		return PTR_ERR(bl);
	}

	bl->props.max_brightness = max_isel;
	bl->props.brightness = max_isel;

	platform_set_drvdata(pdev, bl);

	/* Disable the DCDC if it was started so we can bootstrap */
	wm831x_set_bits(wm831x, WM831X_DCDC_ENABLE, WM831X_DC4_ENA, 0);


	backlight_update_status(bl);

	return 0;
}