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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {unsigned int n_subdevices; struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {void* prealloc_buf; } ;

/* Variables and functions */
 int EINVAL ; 

int comedi_map(void *d, unsigned int subdevice, void *ptr)
{
	struct comedi_device *dev = (struct comedi_device *)d;
	struct comedi_subdevice *s;

	if (subdevice >= dev->n_subdevices)
		return -EINVAL;

	s = dev->subdevices + subdevice;

	if (!s->async)
		return -EINVAL;

	if (ptr)
		*((void **)ptr) = s->async->prealloc_buf;

	/* XXX no reference counting */

	return 0;
}