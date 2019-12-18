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
struct comedi_subdevice {int n_chan; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int do_bits; } ;

/* Variables and functions */
 scalar_t__ DAS1800_DIGITAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int das1800_do_wbits(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	unsigned int wbits;

	/*  only set bits that have been masked */
	data[0] &= (1 << s->n_chan) - 1;
	wbits = devpriv->do_bits;
	wbits &= ~data[0];
	wbits |= data[0] & data[1];
	devpriv->do_bits = wbits;

	outb(devpriv->do_bits, dev->iobase + DAS1800_DIGITAL);

	data[1] = devpriv->do_bits;

	return 2;
}