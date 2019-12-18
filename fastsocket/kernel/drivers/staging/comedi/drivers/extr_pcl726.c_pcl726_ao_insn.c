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
struct TYPE_2__ {unsigned int* ao_readback; scalar_t__* bipolar; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ PCL726_DAC0_HI ; 
 scalar_t__ PCL726_DAC0_LO ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int pcl726_ao_insn(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int hi, lo;
	int n;
	int chan = CR_CHAN(insn->chanspec);

	for (n = 0; n < insn->n; n++) {
		lo = data[n] & 0xff;
		hi = (data[n] >> 8) & 0xf;
		if (devpriv->bipolar[chan])
			hi ^= 0x8;
		/*
		 * the programming info did not say which order
		 * to write bytes.  switch the order of the next
		 * two lines if you get glitches.
		 */
		outb(hi, dev->iobase + PCL726_DAC0_HI + 2 * chan);
		outb(lo, dev->iobase + PCL726_DAC0_LO + 2 * chan);
		devpriv->ao_readback[chan] = data[n];
	}

	return n;
}