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
struct input_dev {int (* getkeycode ) (struct input_dev*,int,int*) ;int (* setkeycode ) (struct input_dev*,int,int) ;int /*<<< orphan*/  event_lock; scalar_t__ sync; int /*<<< orphan*/  key; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int KEY_MAX ; 
 int SYN_REPORT ; 
 scalar_t__ __test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_pass_event (struct input_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_event_supported (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct input_dev*,int,int*) ; 
 int stub2 (struct input_dev*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int input_set_keycode(struct input_dev *dev, int scancode, int keycode)
{
	unsigned long flags;
	int old_keycode;
	int retval;

	if (scancode < 0)
		return -EINVAL;

	if (keycode < 0 || keycode > KEY_MAX)
		return -EINVAL;

	spin_lock_irqsave(&dev->event_lock, flags);

	retval = dev->getkeycode(dev, scancode, &old_keycode);
	if (retval)
		goto out;

	retval = dev->setkeycode(dev, scancode, keycode);
	if (retval)
		goto out;

	/*
	 * Simulate keyup event if keycode is not present
	 * in the keymap anymore
	 */
	if (test_bit(EV_KEY, dev->evbit) &&
	    !is_event_supported(old_keycode, dev->keybit, KEY_MAX) &&
	    __test_and_clear_bit(old_keycode, dev->key)) {

		input_pass_event(dev, EV_KEY, old_keycode, 0);
		if (dev->sync)
			input_pass_event(dev, EV_SYN, SYN_REPORT, 1);
	}

 out:
	spin_unlock_irqrestore(&dev->event_lock, flags);

	return retval;
}