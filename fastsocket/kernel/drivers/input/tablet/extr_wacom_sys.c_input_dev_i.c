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
struct input_dev {int* evbit; int* mscbit; int* relbit; int* keybit; } ;
struct TYPE_2__ {int distance_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_RZ ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_TILT_X ; 
 int /*<<< orphan*/  ABS_TILT_Y ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int BIT_MASK (int /*<<< orphan*/ ) ; 
 size_t BIT_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTN_DIGI ; 
 int /*<<< orphan*/  BTN_EXTRA ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_MOUSE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_LENS ; 
 int /*<<< orphan*/  BTN_TOOL_MOUSE ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void input_dev_i(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	input_dev->evbit[0] |= BIT_MASK(EV_MSC) | BIT_MASK(EV_REL);
	input_dev->mscbit[0] |= BIT_MASK(MSC_SERIAL);
	input_dev->relbit[0] |= BIT_MASK(REL_WHEEL);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] |= BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_MIDDLE) |
		BIT_MASK(BTN_SIDE) | BIT_MASK(BTN_EXTRA);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_TOOL_RUBBER) |
		BIT_MASK(BTN_TOOL_PEN) | BIT_MASK(BTN_STYLUS) |
		BIT_MASK(BTN_TOOL_MOUSE) | BIT_MASK(BTN_TOOL_BRUSH) |
		BIT_MASK(BTN_TOOL_PENCIL) | BIT_MASK(BTN_TOOL_AIRBRUSH) |
		BIT_MASK(BTN_TOOL_LENS) | BIT_MASK(BTN_STYLUS2);
	input_set_abs_params(input_dev, ABS_DISTANCE, 0, wacom_wac->features->distance_max, 0, 0);
	input_set_abs_params(input_dev, ABS_WHEEL, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_X, 0, 127, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_Y, 0, 127, 0, 0);
	input_set_abs_params(input_dev, ABS_RZ, -900, 899, 0, 0);
	input_set_abs_params(input_dev, ABS_THROTTLE, -1023, 1023, 0, 0);
}