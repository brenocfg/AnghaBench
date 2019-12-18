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
struct hid_device_id {unsigned long driver_data; } ;
struct hid_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 unsigned int HID_CONNECT_DEFAULT ; 
 unsigned int HID_CONNECT_FF ; 
 int /*<<< orphan*/  HID_QUIRK_NOGET ; 
 unsigned long LG_FF ; 
 unsigned long LG_FF2 ; 
 unsigned long LG_NOGET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hid_hw_start (struct hid_device*,unsigned int) ; 
 int hid_parse (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,void*) ; 
 int /*<<< orphan*/  lg2ff_init (struct hid_device*) ; 
 int /*<<< orphan*/  lgff_init (struct hid_device*) ; 

__attribute__((used)) static int lg_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	unsigned long quirks = id->driver_data;
	unsigned int connect_mask = HID_CONNECT_DEFAULT;
	int ret;

	hid_set_drvdata(hdev, (void *)quirks);

	if (quirks & LG_NOGET)
		hdev->quirks |= HID_QUIRK_NOGET;

	ret = hid_parse(hdev);
	if (ret) {
		dev_err(&hdev->dev, "parse failed\n");
		goto err_free;
	}

	if (quirks & (LG_FF | LG_FF2))
		connect_mask &= ~HID_CONNECT_FF;

	ret = hid_hw_start(hdev, connect_mask);
	if (ret) {
		dev_err(&hdev->dev, "hw start failed\n");
		goto err_free;
	}

	if (quirks & LG_FF)
		lgff_init(hdev);
	if (quirks & LG_FF2)
		lg2ff_init(hdev);

	return 0;
err_free:
	return ret;
}