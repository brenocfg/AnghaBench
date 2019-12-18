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
struct hid_device {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned char HIDP_DATA_RTYPE_FEATURE ; 
 unsigned char HIDP_DATA_RTYPE_OUPUT ; 
 unsigned char HIDP_TRANS_DATA ; 
 unsigned char HIDP_TRANS_SET_REPORT ; 
#define  HID_FEATURE_REPORT 129 
#define  HID_OUTPUT_REPORT 128 
 scalar_t__ hidp_send_ctrl_message (int /*<<< orphan*/ ,unsigned char,unsigned char*,size_t) ; 

__attribute__((used)) static int hidp_output_raw_report(struct hid_device *hid, unsigned char *data, size_t count,
		unsigned char report_type)
{
	switch (report_type) {
	case HID_FEATURE_REPORT:
		report_type = HIDP_TRANS_SET_REPORT | HIDP_DATA_RTYPE_FEATURE;
		break;
	case HID_OUTPUT_REPORT:
		report_type = HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT;
		break;
	default:
		return -EINVAL;
	}

	if (hidp_send_ctrl_message(hid->driver_data, report_type,
			data, count))
		return -ENOMEM;
	return count;
}