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
struct hid_device_id {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HID_CONNECT_DEFAULT ; 
 int HID_CONNECT_FF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  drff_init (struct hid_device*) ; 
 int hid_hw_start (struct hid_device*,int) ; 
 int hid_parse (struct hid_device*) ; 

__attribute__((used)) static int dr_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;

	dev_dbg(&hdev->dev, "DragonRise Inc. HID hardware probe...");

	ret = hid_parse(hdev);
	if (ret) {
		dev_err(&hdev->dev, "parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (ret) {
		dev_err(&hdev->dev, "hw start failed\n");
		goto err;
	}

	drff_init(hdev);

	return 0;
err:
	return ret;
}