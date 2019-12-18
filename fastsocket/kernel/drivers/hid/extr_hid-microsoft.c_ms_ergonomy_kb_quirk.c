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
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;
struct hid_usage {int hid; } ;
struct hid_input {struct input_dev* input; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_REP ; 
 int HID_USAGE ; 
 int /*<<< orphan*/  KEY_CHAT ; 
 int /*<<< orphan*/  KEY_F13 ; 
 int /*<<< orphan*/  KEY_F14 ; 
 int /*<<< orphan*/  KEY_F15 ; 
 int /*<<< orphan*/  KEY_F16 ; 
 int /*<<< orphan*/  KEY_F17 ; 
 int /*<<< orphan*/  KEY_F18 ; 
 int /*<<< orphan*/  KEY_PHONE ; 
 int /*<<< orphan*/  ms_map_key_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ms_ergonomy_kb_quirk(struct hid_input *hi, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	struct input_dev *input = hi->input;

	switch (usage->hid & HID_USAGE) {
	case 0xfd06: ms_map_key_clear(KEY_CHAT);	break;
	case 0xfd07: ms_map_key_clear(KEY_PHONE);	break;
	case 0xff05:
		set_bit(EV_REP, input->evbit);
		ms_map_key_clear(KEY_F13);
		set_bit(KEY_F14, input->keybit);
		set_bit(KEY_F15, input->keybit);
		set_bit(KEY_F16, input->keybit);
		set_bit(KEY_F17, input->keybit);
		set_bit(KEY_F18, input->keybit);
	default:
		return 0;
	}
	return 1;
}