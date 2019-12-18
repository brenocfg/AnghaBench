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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  attached; struct comedi_subdevice* subdevices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  ntrig; } ;
struct TYPE_5__ {scalar_t__ is_8112; } ;
struct TYPE_4__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PCL711_AD_HI ; 
 scalar_t__ PCL711_AD_LO ; 
 scalar_t__ PCL711_CLRINTR ; 
 scalar_t__ PCL711_MODE ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_3__* devpriv ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_2__* this_board ; 

__attribute__((used)) static irqreturn_t pcl711_interrupt(int irq, void *d)
{
	int lo, hi;
	int data;
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->subdevices + 0;

	if (!dev->attached) {
		comedi_error(dev, "spurious interrupt");
		return IRQ_HANDLED;
	}

	hi = inb(dev->iobase + PCL711_AD_HI);
	lo = inb(dev->iobase + PCL711_AD_LO);
	outb(0, dev->iobase + PCL711_CLRINTR);

	data = (hi << 8) | lo;

	/* FIXME! Nothing else sets ntrig! */
	if (!(--devpriv->ntrig)) {
		if (this_board->is_8112) {
			outb(1, dev->iobase + PCL711_MODE);
		} else {
			outb(0, dev->iobase + PCL711_MODE);
		}

		s->async->events |= COMEDI_CB_EOA;
	}
	comedi_event(dev, s);
	return IRQ_HANDLED;
}