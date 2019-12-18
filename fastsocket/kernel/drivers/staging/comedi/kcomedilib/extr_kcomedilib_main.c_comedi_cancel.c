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
struct comedi_subdevice {void* lock; void* busy; int (* cancel ) (struct comedi_device*,struct comedi_subdevice*) ;TYPE_1__* async; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int SRF_RT ; 
 int SRF_RUNNING ; 
 int /*<<< orphan*/  comedi_set_subdevice_runflags (struct comedi_subdevice*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct comedi_device*,struct comedi_subdevice*) ; 

int comedi_cancel(void *d, unsigned int subdevice)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;
	int ret = 0;

	if (subdevice >= dev->n_subdevices)
		return -EINVAL;

	s = dev->subdevices + subdevice;

	if (s->lock && s->lock != d)
		return -EACCES;

#if 0
	if (!s->busy)
		return 0;

	if (s->busy != d)
		return -EBUSY;
#endif

	if (!s->cancel || !s->async)
		return -EINVAL;

	ret = s->cancel(dev, s);

	if (ret)
		return ret;

	comedi_set_subdevice_runflags(s, SRF_RUNNING | SRF_RT, 0);
	s->async->inttrig = NULL;
	s->busy = NULL;

	return 0;
}