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
struct comedi_subdevice {void* lock; int /*<<< orphan*/  spin_lock; scalar_t__ busy; struct comedi_async* async; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_async {int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * cb_func; scalar_t__ cb_mask; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int comedi_unlock(void *d, unsigned int subdevice)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	unsigned long flags;
	struct comedi_async *async;
	int ret;

	if (subdevice >= dev->n_subdevices)
		return -EINVAL;

	s = dev->subdevices + subdevice;

	async = s->async;

	spin_lock_irqsave(&s->spin_lock, flags);

	if (s->busy) {
		ret = -EBUSY;
	} else if (s->lock && s->lock != (void *)d) {
		ret = -EACCES;
	} else {
		s->lock = NULL;

		if (async) {
			async->cb_mask = 0;
			async->cb_func = NULL;
			async->cb_arg = NULL;
		}

		ret = 0;
	}

	spin_unlock_irqrestore(&s->spin_lock, flags);

	return ret;
}