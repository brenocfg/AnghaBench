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
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  minor; struct comedi_subdevice* subdevices; } ;
struct TYPE_6__ {int ai_data_len; scalar_t__ ai_act_scan; scalar_t__ ai_scans; int /*<<< orphan*/  neverending_ai; } ;
struct TYPE_5__ {int fifo_half_size; } ;
struct TYPE_4__ {int events; } ;

/* Variables and functions */
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 scalar_t__ PCI171x_CLRINT ; 
 scalar_t__ PCI171x_STATUS ; 
 int Status_FF ; 
 int Status_FH ; 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 TYPE_3__* devpriv ; 
 int inw (scalar_t__) ; 
 scalar_t__ move_block_from_fifo (struct comedi_device*,struct comedi_subdevice*,int,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci171x_ai_cancel (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* this_board ; 

__attribute__((used)) static void interrupt_pci1710_half_fifo(void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s = dev->subdevices + 0;
	int m, samplesinbuf;

	DPRINTK("adv_pci1710 EDBG: BGN: interrupt_pci1710_half_fifo(...)\n");
	m = inw(dev->iobase + PCI171x_STATUS);
	if (!(m & Status_FH)) {
		printk("comedi%d: A/D FIFO not half full! (%4x)\n",
		       dev->minor, m);
		pci171x_ai_cancel(dev, s);
		s->async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
		comedi_event(dev, s);
		return;
	}
	if (m & Status_FF) {
		printk
		    ("comedi%d: A/D FIFO Full status (Fatal Error!) (%4x)\n",
		     dev->minor, m);
		pci171x_ai_cancel(dev, s);
		s->async->events |= COMEDI_CB_EOA | COMEDI_CB_ERROR;
		comedi_event(dev, s);
		return;
	}

	samplesinbuf = this_board->fifo_half_size;
	if (samplesinbuf * sizeof(short) >= devpriv->ai_data_len) {
		m = devpriv->ai_data_len / sizeof(short);
		if (move_block_from_fifo(dev, s, m, 0))
			return;
		samplesinbuf -= m;
	}

	if (samplesinbuf) {
		if (move_block_from_fifo(dev, s, samplesinbuf, 1))
			return;
	}

	if (!devpriv->neverending_ai)
		if (devpriv->ai_act_scan >= devpriv->ai_scans) {	/* all data sampled */
			pci171x_ai_cancel(dev, s);
			s->async->events |= COMEDI_CB_EOA;
			comedi_event(dev, s);
			return;
		}
	outb(0, dev->iobase + PCI171x_CLRINT);	/*  clear our INT request */
	DPRINTK("adv_pci1710 EDBG: END: interrupt_pci1710_half_fifo(...)\n");

	comedi_event(dev, s);
}