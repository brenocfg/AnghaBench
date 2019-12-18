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
struct input_dev {int* evbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  relbit; } ;
struct hid_usage {int dummy; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_field {int dummy; } ;
struct hid_device {int product; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_MISC ; 
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_5 ; 
 int /*<<< orphan*/  BTN_6 ; 
 int /*<<< orphan*/  BTN_7 ; 
 int /*<<< orphan*/  BTN_8 ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_MOUSE ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
#define  USB_DEVICE_ID_WACOM_GRAPHIRE_BLUETOOTH 129 
#define  USB_DEVICE_ID_WACOM_INTUOS4_BLUETOOTH 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_input_mapped(struct hid_device *hdev, struct hid_input *hi,
	struct hid_field *field, struct hid_usage *usage, unsigned long **bit,
								int *max)
{
	struct input_dev *input = hi->input;

	/* Basics */
	input->evbit[0] |= BIT(EV_KEY) | BIT(EV_ABS) | BIT(EV_REL);

	__set_bit(REL_WHEEL, input->relbit);

	__set_bit(BTN_TOOL_PEN, input->keybit);
	__set_bit(BTN_TOUCH, input->keybit);
	__set_bit(BTN_STYLUS, input->keybit);
	__set_bit(BTN_STYLUS2, input->keybit);
	__set_bit(BTN_LEFT, input->keybit);
	__set_bit(BTN_RIGHT, input->keybit);
	__set_bit(BTN_MIDDLE, input->keybit);

	/* Pad */
	input->evbit[0] |= BIT(EV_MSC);

	__set_bit(MSC_SERIAL, input->mscbit);

	__set_bit(BTN_0, input->keybit);
	__set_bit(BTN_1, input->keybit);
	__set_bit(BTN_TOOL_FINGER, input->keybit);

	/* Distance, rubber and mouse */
	__set_bit(BTN_TOOL_RUBBER, input->keybit);
	__set_bit(BTN_TOOL_MOUSE, input->keybit);

	switch (hdev->product) {
	case USB_DEVICE_ID_WACOM_GRAPHIRE_BLUETOOTH:
		input_set_abs_params(input, ABS_X, 0, 16704, 4, 0);
		input_set_abs_params(input, ABS_Y, 0, 12064, 4, 0);
		input_set_abs_params(input, ABS_PRESSURE, 0, 511, 0, 0);
		input_set_abs_params(input, ABS_DISTANCE, 0, 32, 0, 0);
		break;
	case USB_DEVICE_ID_WACOM_INTUOS4_BLUETOOTH:
		__set_bit(ABS_MISC, input->absbit);
		__set_bit(BTN_2, input->keybit);
		__set_bit(BTN_3, input->keybit);
		__set_bit(BTN_4, input->keybit);
		__set_bit(BTN_5, input->keybit);
		__set_bit(BTN_6, input->keybit);
		__set_bit(BTN_7, input->keybit);
		__set_bit(BTN_8, input->keybit);
		input_set_abs_params(input, ABS_X, 0, 40640, 4, 0);
		input_set_abs_params(input, ABS_Y, 0, 25400, 4, 0);
		input_set_abs_params(input, ABS_PRESSURE, 0, 2047, 0, 0);
		input_set_abs_params(input, ABS_DISTANCE, 0, 63, 0, 0);
		break;
	}

	return 0;
}