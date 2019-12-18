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
struct comedi_device {scalar_t__ attached; struct comedi_subdevice* subdevices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int events; } ;

/* Variables and functions */
 int COMEDI_CB_BLOCK ; 
 int COMEDI_CB_EOS ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  comedi_buf_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int pc236_intr_check (struct comedi_device*) ; 

__attribute__((used)) static irqreturn_t pc236_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->subdevices + 1;
	int handled;

	handled = pc236_intr_check(dev);
	if (dev->attached && handled) {
		comedi_buf_put(s->async, 0);
		s->async->events |= COMEDI_CB_BLOCK | COMEDI_CB_EOS;
		comedi_event(dev, s);
	}
	return IRQ_RETVAL(handled);
}