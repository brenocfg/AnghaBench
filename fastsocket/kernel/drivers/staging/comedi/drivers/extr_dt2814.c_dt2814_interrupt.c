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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  ntrig; } ;
struct TYPE_3__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 scalar_t__ DT2814_CSR ; 
 scalar_t__ DT2814_DATA ; 
 int DT2814_FINISH ; 
 int DT2814_TIMEOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_2__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t dt2814_interrupt(int irq, void *d)
{
	int lo, hi;
	struct comedi_device *dev = d;
	struct comedi_subdevice *s;
	int data;

	if (!dev->attached) {
		comedi_error(dev, "spurious interrupt");
		return IRQ_HANDLED;
	}

	s = dev->subdevices + 0;

	hi = inb(dev->iobase + DT2814_DATA);
	lo = inb(dev->iobase + DT2814_DATA);

	data = (hi << 4) | (lo >> 4);

	if (!(--devpriv->ntrig)) {
		int i;

		outb(0, dev->iobase + DT2814_CSR);
		/* note: turning off timed mode triggers another
		   sample. */

		for (i = 0; i < DT2814_TIMEOUT; i++) {
			if (inb(dev->iobase + DT2814_CSR) & DT2814_FINISH)
				break;
		}
		inb(dev->iobase + DT2814_DATA);
		inb(dev->iobase + DT2814_DATA);

		s->async->events |= COMEDI_CB_EOA;
	}
	comedi_event(dev, s);
	return IRQ_HANDLED;
}