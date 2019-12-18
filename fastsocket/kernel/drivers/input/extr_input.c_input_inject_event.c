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
struct input_handle {struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  event_lock; int /*<<< orphan*/  grab; int /*<<< orphan*/  evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_MAX ; 
 int /*<<< orphan*/  input_handle_event (struct input_dev*,unsigned int,unsigned int,int) ; 
 scalar_t__ is_event_supported (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct input_handle* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void input_inject_event(struct input_handle *handle,
			unsigned int type, unsigned int code, int value)
{
	struct input_dev *dev = handle->dev;
	struct input_handle *grab;
	unsigned long flags;

	if (is_event_supported(type, dev->evbit, EV_MAX)) {
		spin_lock_irqsave(&dev->event_lock, flags);

		rcu_read_lock();
		grab = rcu_dereference(dev->grab);
		if (!grab || grab == handle)
			input_handle_event(dev, type, code, value);
		rcu_read_unlock();

		spin_unlock_irqrestore(&dev->event_lock, flags);
	}
}