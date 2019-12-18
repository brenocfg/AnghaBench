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
struct comedi_subdevice {scalar_t__ type; void* lock; scalar_t__ busy; struct comedi_async* async; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_async {unsigned int cb_mask; int (* cb_func ) (unsigned int,void*) ;int /*<<< orphan*/ * cb_arg; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 

int comedi_register_callback(void *d, unsigned int subdevice,
			     unsigned int mask, int (*cb) (unsigned int,
							   void *), void *arg)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	struct comedi_async *async;

	if (subdevice >= dev->n_subdevices)
		return -EINVAL;

	s = dev->subdevices + subdevice;

	async = s->async;
	if (s->type == COMEDI_SUBD_UNUSED || !async)
		return -EIO;

	/* are we locked? (ioctl lock) */
	if (s->lock && s->lock != d)
		return -EACCES;

	/* are we busy? */
	if (s->busy)
		return -EBUSY;

	if (!mask) {
		async->cb_mask = 0;
		async->cb_func = NULL;
		async->cb_arg = NULL;
	} else {
		async->cb_mask = mask;
		async->cb_func = cb;
		async->cb_arg = arg;
	}

	return 0;
}