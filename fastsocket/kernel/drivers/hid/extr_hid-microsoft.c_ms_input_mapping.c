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
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HID_UP_MSVENDOR ; 
 int HID_USAGE_PAGE ; 
 unsigned long MS_ERGONOMY ; 
 unsigned long MS_PRESENTER ; 
 scalar_t__ hid_get_drvdata (struct hid_device*) ; 
 int ms_ergonomy_kb_quirk (struct hid_input*,struct hid_usage*,unsigned long**,int*) ; 
 scalar_t__ ms_presenter_8k_quirk (struct hid_input*,struct hid_usage*,unsigned long**,int*) ; 

__attribute__((used)) static int ms_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	unsigned long quirks = (unsigned long)hid_get_drvdata(hdev);

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		return 0;

	if (quirks & MS_ERGONOMY) {
		int ret = ms_ergonomy_kb_quirk(hi, usage, bit, max);
		if (ret)
			return ret;
	}

	if ((quirks & MS_PRESENTER) &&
			ms_presenter_8k_quirk(hi, usage, bit, max))
		return 1;

	return 0;
}