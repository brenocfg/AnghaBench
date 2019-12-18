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
struct input_dev {int /*<<< orphan*/  event_lock; scalar_t__* rep; int /*<<< orphan*/  timer; scalar_t__ sync; int /*<<< orphan*/  repeat_key; int /*<<< orphan*/  keybit; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  KEY_MAX ; 
 size_t REP_PERIOD ; 
 int /*<<< orphan*/  SYN_REPORT ; 
 int /*<<< orphan*/  input_pass_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_event_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_repeat_key(unsigned long data)
{
	struct input_dev *dev = (void *) data;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	if (test_bit(dev->repeat_key, dev->key) &&
	    is_event_supported(dev->repeat_key, dev->keybit, KEY_MAX)) {

		input_pass_event(dev, EV_KEY, dev->repeat_key, 2);

		if (dev->sync) {
			/*
			 * Only send SYN_REPORT if we are not in a middle
			 * of driver parsing a new hardware packet.
			 * Otherwise assume that the driver will send
			 * SYN_REPORT once it's done.
			 */
			input_pass_event(dev, EV_SYN, SYN_REPORT, 1);
		}

		if (dev->rep[REP_PERIOD])
			mod_timer(&dev->timer, jiffies +
					msecs_to_jiffies(dev->rep[REP_PERIOD]));
	}

	spin_unlock_irqrestore(&dev->event_lock, flags);
}