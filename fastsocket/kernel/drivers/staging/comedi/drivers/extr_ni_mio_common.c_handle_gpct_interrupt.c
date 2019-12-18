#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_6__ {TYPE_1__* counter_dev; } ;
struct TYPE_5__ {scalar_t__ events; } ;
struct TYPE_4__ {int /*<<< orphan*/ * counters; } ;

/* Variables and functions */
 int NI_GPCT_SUBDEV (unsigned short) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  ni_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  ni_tio_handle_interrupt (int /*<<< orphan*/ *,struct comedi_subdevice*) ; 

__attribute__((used)) static void handle_gpct_interrupt(struct comedi_device *dev,
				  unsigned short counter_index)
{
#ifdef PCIDMA
	struct comedi_subdevice *s =
	    dev->subdevices + NI_GPCT_SUBDEV(counter_index);

	ni_tio_handle_interrupt(&devpriv->counter_dev->counters[counter_index],
				s);
	if (s->async->events)
		ni_event(dev, s);
#endif
}