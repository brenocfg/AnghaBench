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
struct input_dev {int /*<<< orphan*/  ffbit; struct ff_device* ff; } ;
struct ff_device {int /*<<< orphan*/  (* playback ) (struct input_dev*,unsigned int,int) ;int /*<<< orphan*/  (* set_autocenter ) (struct input_dev*,int) ;int /*<<< orphan*/  (* set_gain ) (struct input_dev*,int) ;} ;

/* Variables and functions */
 unsigned int EV_FF ; 
#define  FF_AUTOCENTER 129 
#define  FF_GAIN 128 
 int /*<<< orphan*/  check_effect_access (struct ff_device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct input_dev*,int) ; 
 int /*<<< orphan*/  stub2 (struct input_dev*,int) ; 
 int /*<<< orphan*/  stub3 (struct input_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  test_bit (int const,int /*<<< orphan*/ ) ; 

int input_ff_event(struct input_dev *dev, unsigned int type,
		   unsigned int code, int value)
{
	struct ff_device *ff = dev->ff;

	if (type != EV_FF)
		return 0;

	switch (code) {
	case FF_GAIN:
		if (!test_bit(FF_GAIN, dev->ffbit) || value > 0xffff)
			break;

		ff->set_gain(dev, value);
		break;

	case FF_AUTOCENTER:
		if (!test_bit(FF_AUTOCENTER, dev->ffbit) || value > 0xffff)
			break;

		ff->set_autocenter(dev, value);
		break;

	default:
		if (check_effect_access(ff, code, NULL) == 0)
			ff->playback(dev, code, value);
		break;
	}

	return 0;
}