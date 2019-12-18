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
struct comedi_subdevice {scalar_t__ type; void* lock; int (* poll ) (struct comedi_device*,struct comedi_subdevice*) ;int /*<<< orphan*/  busy; struct comedi_async* async; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct comedi_async {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_UNUSED ; 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

int comedi_poll(void *d, unsigned int subdevice)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s = dev->subdevices;
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

	/* are we running? XXX wrong? */
	if (!s->busy)
		return -EIO;

	return s->poll(dev, s);
}