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
struct input_dev {int* keybit; int* evbit; int* mscbit; } ;
struct TYPE_2__ {int distance_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DISTANCE ; 
 int /*<<< orphan*/  ABS_RX ; 
 int /*<<< orphan*/  ABS_RY ; 
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
 int /*<<< orphan*/  BTN_DIGI ; 
 int /*<<< orphan*/  BTN_MISC ; 
 int /*<<< orphan*/  BTN_STYLUS ; 
 int /*<<< orphan*/  BTN_STYLUS2 ; 
 int /*<<< orphan*/  BTN_TOOL_AIRBRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_BRUSH ; 
 int /*<<< orphan*/  BTN_TOOL_FINGER ; 
 int /*<<< orphan*/  BTN_TOOL_PEN ; 
 int /*<<< orphan*/  BTN_TOOL_PENCIL ; 
 int /*<<< orphan*/  BTN_TOOL_RUBBER ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SERIAL ; 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void input_dev_cintiq(struct input_dev *input_dev, struct wacom_wac *wacom_wac)
{
	input_dev->keybit[BIT_WORD(BTN_MISC)] |= BIT_MASK(BTN_0) | BIT_MASK(BTN_1) | BIT_MASK(BTN_2) | BIT_MASK(BTN_3);
	input_dev->keybit[BIT_WORD(BTN_MISC)] |= BIT_MASK(BTN_4) | BIT_MASK(BTN_5) | BIT_MASK(BTN_6) | BIT_MASK(BTN_7);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_TOOL_FINGER);

	input_set_abs_params(input_dev, ABS_RX, 0, 4096, 0, 0);
	input_set_abs_params(input_dev, ABS_RY, 0, 4096, 0, 0);
	input_set_abs_params(input_dev, ABS_Z, -900, 899, 0, 0);

	input_dev->evbit[0] |= BIT_MASK(EV_MSC);
	input_dev->mscbit[0] |= BIT_MASK(MSC_SERIAL);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_TOOL_RUBBER) |
		BIT_MASK(BTN_TOOL_PEN) | BIT_MASK(BTN_TOOL_BRUSH) |
		BIT_MASK(BTN_TOOL_PENCIL) | BIT_MASK(BTN_TOOL_AIRBRUSH);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |= BIT_MASK(BTN_STYLUS) | BIT_MASK(BTN_STYLUS2);

	input_set_abs_params(input_dev, ABS_DISTANCE, 0, wacom_wac->features->distance_max, 0, 0);
	input_set_abs_params(input_dev, ABS_WHEEL, 0, 1023, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_X, 0, 127, 0, 0);
	input_set_abs_params(input_dev, ABS_TILT_Y, 0, 127, 0, 0);
}