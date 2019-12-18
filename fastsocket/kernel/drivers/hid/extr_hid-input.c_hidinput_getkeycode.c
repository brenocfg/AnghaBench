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
struct input_dev {int dummy; } ;
struct hid_usage {int code; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct hid_usage* hidinput_find_key (struct hid_device*,int,int /*<<< orphan*/ ) ; 
 struct hid_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int hidinput_getkeycode(struct input_dev *dev, int scancode,
				int *keycode)
{
	struct hid_device *hid = input_get_drvdata(dev);
	struct hid_usage *usage;

	usage = hidinput_find_key(hid, scancode, 0);
	if (usage) {
		*keycode = usage->code;
		return 0;
	}
	return -EINVAL;
}