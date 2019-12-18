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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int* ao_readback; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ DT2815_DATA ; 
 int EBUSY ; 
 TYPE_1__* devpriv ; 
 unsigned int dt2815_wait_for_status (struct comedi_device*,int) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int) ; 

__attribute__((used)) static int dt2815_ao_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int i;
	int chan = CR_CHAN(insn->chanspec);
	unsigned int status;
	unsigned int lo, hi;

	for (i = 0; i < insn->n; i++) {
		lo = ((data[i] & 0x0f) << 4) | (chan << 1) | 0x01;
		hi = (data[i] & 0xff0) >> 4;

		status = dt2815_wait_for_status(dev, 0x00);
		if (status != 0) {
			printk
			    ("dt2815: failed to write low byte on %d reason %x\n",
			     chan, status);
			return -EBUSY;
		}

		outb(lo, dev->iobase + DT2815_DATA);

		status = dt2815_wait_for_status(dev, 0x10);
		if (status != 0x10) {
			printk
			    ("dt2815: failed to write high byte on %d reason %x\n",
			     chan, status);
			return -EBUSY;
		}
		devpriv->ao_readback[chan] = data[i];
	}
	return i;
}