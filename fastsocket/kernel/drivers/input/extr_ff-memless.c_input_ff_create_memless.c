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
struct ml_device {int (* play_effect ) (struct input_dev*,void*,struct ff_effect*) ;int gain; TYPE_1__* states; int /*<<< orphan*/  timer; void* private; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  ffbit; struct ff_device* ff; } ;
struct ff_device {int /*<<< orphan*/ * effects; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  destroy; int /*<<< orphan*/  set_gain; int /*<<< orphan*/  playback; int /*<<< orphan*/  upload; struct ml_device* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * effect; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FF_GAIN ; 
 int FF_MEMLESS_EFFECTS ; 
 int /*<<< orphan*/  FF_PERIODIC ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  FF_SINE ; 
 int /*<<< orphan*/  FF_SQUARE ; 
 int /*<<< orphan*/  FF_TRIANGLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int input_ff_create (struct input_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct ml_device*) ; 
 struct ml_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_effect_timer ; 
 int /*<<< orphan*/  ml_ff_destroy ; 
 int /*<<< orphan*/  ml_ff_playback ; 
 int /*<<< orphan*/  ml_ff_set_gain ; 
 int /*<<< orphan*/  ml_ff_upload ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int input_ff_create_memless(struct input_dev *dev, void *data,
		int (*play_effect)(struct input_dev *, void *, struct ff_effect *))
{
	struct ml_device *ml;
	struct ff_device *ff;
	int error;
	int i;

	ml = kzalloc(sizeof(struct ml_device), GFP_KERNEL);
	if (!ml)
		return -ENOMEM;

	ml->dev = dev;
	ml->private = data;
	ml->play_effect = play_effect;
	ml->gain = 0xffff;
	setup_timer(&ml->timer, ml_effect_timer, (unsigned long)dev);

	set_bit(FF_GAIN, dev->ffbit);

	error = input_ff_create(dev, FF_MEMLESS_EFFECTS);
	if (error) {
		kfree(ml);
		return error;
	}

	ff = dev->ff;
	ff->private = ml;
	ff->upload = ml_ff_upload;
	ff->playback = ml_ff_playback;
	ff->set_gain = ml_ff_set_gain;
	ff->destroy = ml_ff_destroy;

	/* we can emulate periodic effects with RUMBLE */
	if (test_bit(FF_RUMBLE, ff->ffbit)) {
		set_bit(FF_PERIODIC, dev->ffbit);
		set_bit(FF_SINE, dev->ffbit);
		set_bit(FF_TRIANGLE, dev->ffbit);
		set_bit(FF_SQUARE, dev->ffbit);
	}

	for (i = 0; i < FF_MEMLESS_EFFECTS; i++)
		ml->states[i].effect = &ff->effects[i];

	return 0;
}