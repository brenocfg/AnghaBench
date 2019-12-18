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
struct wacom_data {unsigned char features; } ;
struct input_dev {int dummy; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  wacom_i4_parse_button_report (struct wacom_data*,struct input_dev*,unsigned char*) ; 
 int /*<<< orphan*/  wacom_i4_parse_pen_report (struct wacom_data*,struct input_dev*,unsigned char*) ; 

__attribute__((used)) static void wacom_i4_parse_report(struct hid_device *hdev,
			struct wacom_data *wdata,
			struct input_dev *input, unsigned char *data)
{
	switch (data[0]) {
	case 0x00: /* Empty report */
		break;
	case 0x02: /* Pen report */
		wacom_i4_parse_pen_report(wdata, input, data);
		break;
	case 0x03: /* Features Report */
		wdata->features = data[2];
		break;
	case 0x0C: /* Button report */
		wacom_i4_parse_button_report(wdata, input, data);
		break;
	default:
		dev_err(&(hdev)->dev, "Unknown report: %d,%d\n", data[0], data[1]);
		break;
	}
}