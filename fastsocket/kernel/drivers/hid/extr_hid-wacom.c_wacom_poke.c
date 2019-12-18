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
typedef  scalar_t__ u8 ;
struct wacom_data {scalar_t__ high_speed; } ;
struct hid_device {int (* hid_output_raw_report ) (struct hid_device*,char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char,int) ; 
 struct wacom_data* hid_get_drvdata (struct hid_device*) ; 
 int stub1 (struct hid_device*,char*,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct hid_device*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_poke(struct hid_device *hdev, u8 speed)
{
	struct wacom_data *wdata = hid_get_drvdata(hdev);
	int limit, ret;
	char rep_data[2];

	rep_data[0] = 0x03 ; rep_data[1] = 0x00;
	limit = 3;
	do {
		ret = hdev->hid_output_raw_report(hdev, rep_data, 2,
				HID_FEATURE_REPORT);
	} while (ret < 0 && limit-- > 0);

	if (ret >= 0) {
		if (speed == 0)
			rep_data[0] = 0x05;
		else
			rep_data[0] = 0x06;

		rep_data[1] = 0x00;
		limit = 3;
		do {
			ret = hdev->hid_output_raw_report(hdev, rep_data, 2,
					HID_FEATURE_REPORT);
		} while (ret < 0 && limit-- > 0);

		if (ret >= 0) {
			wdata->high_speed = speed;
			return;
		}
	}

	/*
	 * Note that if the raw queries fail, it's not a hard failure and it
	 * is safe to continue
	 */
	dev_warn(&hdev->dev, "failed to poke device, command %d, err %d\n",
				rep_data[0], ret);
	return;
}