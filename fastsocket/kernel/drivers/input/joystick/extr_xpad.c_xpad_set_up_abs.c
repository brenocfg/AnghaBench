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
struct input_dev {int /*<<< orphan*/  absbit; } ;

/* Variables and functions */
#define  ABS_HAT0X 135 
#define  ABS_HAT0Y 134 
#define  ABS_RX 133 
#define  ABS_RY 132 
#define  ABS_RZ 131 
#define  ABS_X 130 
#define  ABS_Y 129 
#define  ABS_Z 128 
 int /*<<< orphan*/  input_set_abs_params (struct input_dev*,short,int,int,int,int) ; 
 int /*<<< orphan*/  set_bit (short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xpad_set_up_abs(struct input_dev *input_dev, signed short abs)
{
	set_bit(abs, input_dev->absbit);

	switch (abs) {
	case ABS_X:
	case ABS_Y:
	case ABS_RX:
	case ABS_RY:	/* the two sticks */
		input_set_abs_params(input_dev, abs, -32768, 32767, 16, 128);
		break;
	case ABS_Z:
	case ABS_RZ:	/* the triggers */
		input_set_abs_params(input_dev, abs, 0, 255, 0, 0);
		break;
	case ABS_HAT0X:
	case ABS_HAT0Y:	/* the d-pad (only if MAP_DPAD_TO_AXES) */
		input_set_abs_params(input_dev, abs, -1, 1, 0, 0);
		break;
	}
}