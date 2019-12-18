#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* async; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; } ;
struct TYPE_4__ {int /*<<< orphan*/  events; } ;
struct TYPE_3__ {int ui_AiNbrofChannels; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOS ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 int comedi_buf_put (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 

int i_APCI3120_InterruptHandleEos(struct comedi_device *dev)
{
	int n_chan, i;
	struct comedi_subdevice *s = dev->subdevices + 0;
	int err = 1;

	n_chan = devpriv->ui_AiNbrofChannels;

	s->async->events = 0;

	for (i = 0; i < n_chan; i++)
		err &= comedi_buf_put(s->async, inw(dev->iobase + 0));

	s->async->events |= COMEDI_CB_EOS;

	if (err == 0)
		s->async->events |= COMEDI_CB_OVERFLOW;

	comedi_event(dev, s);

	return 0;
}