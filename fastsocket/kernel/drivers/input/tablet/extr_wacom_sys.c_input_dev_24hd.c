#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wacom_wac {TYPE_1__* features; } ;
struct input_dev {int* keybit; } ;
struct TYPE_2__ {int distance_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_Z ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_0 ; 
 int /*<<< orphan*/  BTN_1 ; 
 int /*<<< orphan*/  BTN_2 ; 
 int /*<<< orphan*/  BTN_3 ; 
 int /*<<< orphan*/  BTN_4 ; 
 int /*<<< orphan*/  BTN_5 ; 
 int /*<<< orphan*/  BTN_6 ; 
 int /*<<< orphan*/  BTN_7 ; 
 int /*<<< orphan*/  BTN_8 ; 
 int /*<<< orphan*/  BTN_9 ; 
 int /*<<< orphan*/  BTN_A ; 
 int /*<<< orphan*/  BTN_B ; 
 int /*<<< orphan*/  BTN_C ; 
 int /*<<< orphan*/  BTN_GAMEPAD ; 
 int /*<<< orphan*/  BTN_MISC ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  BTN_X ; 
 int /*<<< orphan*/  BTN_Y ; 
 int /*<<< orphan*/  BTN_Z ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  KEY_PLAYCD ; 
 int /*<<< orphan*/  KEY_PROG1 ; 
 int /*<<< orphan*/  KEY_PROG2 ; 
 int /*<<< orphan*/  KEY_PROG3 ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void input_dev_24hd(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	input_dev->keybit[BIT_WORD(BTN_GAMEPAD)] |= BIT_MASK(BTN_A) | BIT_MASK(BTN_B) | BIT_MASK(BTN_C);
	input_dev->keybit[BIT_WORD(BTN_GAMEPAD)] |= BIT_MASK(BTN_X) | BIT_MASK(BTN_Y) | BIT_MASK(BTN_Z);
	input_dev->keybit[BIT_WORD(BTN_MISC)] |= BIT_MASK(BTN_0) | BIT_MASK(BTN_1) | BIT_MASK(BTN_2) |
						 BIT_MASK(BTN_3) | BIT_MASK(BTN_4) | BIT_MASK(BTN_5) |
						 BIT_MASK(BTN_6) | BIT_MASK(BTN_7) | BIT_MASK(BTN_8) |
						 BIT_MASK(BTN_9);
	input_dev->keybit[BIT_WORD(KEY_PROG1)] |= BIT_MASK(KEY_PROG1) | BIT_MASK(KEY_PROG2);
	input_dev->keybit[BIT_WORD(KEY_PLAYCD)] |= BIT_MASK(KEY_PROG3);

	input_set_abs_params(input_dev, ABS_Z, -900, 899, 0, 0);
	input_set_abs_params(input_dev, ABS_THROTTLE, 0, 71, 0, 0);
	input_set_capability(input_dev, EV_MSC, MSC_SERIAL);

	input_dev->keybit[BIT_WORD(BTN_TOOL_RUBBER)] |= BIT_MASK(BTN_TOOL_RUBBER) | BIT_MASK(BTN_TOOL_PEN) |
						BIT_MASK(BTN_TOOL_BRUSH) | BIT_MASK(BTN_TOOL_PENCIL) |
						BIT_MASK(BTN_TOOL_AIRBRUSH) | BIT_MASK(BTN_STYLUS) |
						BIT_MASK(BTN_STYLUS2);

	input_set_abs_params(input_dev, ABS_DISTANCE,
			     0, wacom_wac->features->distance_max, 0, 0);
	input_set_abs_params(input_dev, ABS_WHEEL, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_X, 0, 127, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_Y, 0, 127, 0, 0);
}