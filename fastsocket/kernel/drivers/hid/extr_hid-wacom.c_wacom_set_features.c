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
struct hid_device {int (* hid_output_raw_report ) (struct hid_device*,int*,int,int /*<<< orphan*/ ) ;} ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int stub1 (struct hid_device*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_set_features(struct hid_device *hdev)
{
	int ret;
	__u8 rep_data[2];

	/*set high speed, tablet mode*/
	rep_data[0] = 0x03;
	rep_data[1] = 0x20;
	ret = hdev->hid_output_raw_report(hdev, rep_data, 2,
				HID_FEATURE_REPORT);
	return;
}