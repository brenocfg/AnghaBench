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
struct wacom_data {int /*<<< orphan*/  features; } ;
struct hid_device_id {int dummy; } ;
struct hid_device {int product; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_CONNECT_DEFAULT ; 
#define  USB_DEVICE_ID_WACOM_GRAPHIRE_BLUETOOTH 129 
#define  USB_DEVICE_ID_WACOM_INTUOS4_BLUETOOTH 128 
 int /*<<< orphan*/  dev_attr_speed ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hid_hw_start (struct hid_device*,int /*<<< orphan*/ ) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct wacom_data*) ; 
 int /*<<< orphan*/  kfree (struct wacom_data*) ; 
 struct wacom_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wacom_poke (struct hid_device*,int) ; 
 int /*<<< orphan*/  wacom_set_features (struct hid_device*) ; 

__attribute__((used)) static int wacom_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	struct wacom_data *wdata;
	int ret;

	wdata = kzalloc(sizeof(*wdata), GFP_KERNEL);
	if (wdata == NULL) {
		dev_err(&hdev->dev, "can't alloc wacom descriptor\n");
		return -ENOMEM;
	}

	hid_set_drvdata(hdev, wdata);

	/* Parse the HID report now */
	ret = hid_parse(hdev);
	if (ret) {
		dev_err(&hdev->dev, "parse failed\n");
		goto err_free;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		dev_err(&hdev->dev, "hw start failed\n");
		goto err_free;
	}

	ret = device_create_file(&hdev->dev, &dev_attr_speed);
	if (ret)
		dev_warn(&hdev->dev,
			"can't create sysfs speed attribute err: %d\n", ret);

	switch (hdev->product) {
	case USB_DEVICE_ID_WACOM_GRAPHIRE_BLUETOOTH:
		/* Set Wacom mode 2 with high reporting speed */
		wacom_poke(hdev, 1);
		break;
	case USB_DEVICE_ID_WACOM_INTUOS4_BLUETOOTH:
		wdata->features = 0;
		wacom_set_features(hdev);
		break;
	}

	return 0;
err_free:
	kfree(wdata);
	return ret;
}