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
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int do_bits; } ;

/* Variables and functions */
 scalar_t__ DAS16M1_DIO ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int das16m1_do_wbits(struct comedi_device *dev,
			    struct comedi_subdevice *s,
			    struct comedi_insn *insn, unsigned int *data)
{
	unsigned int wbits;

	/*  only set bits that have been masked */
	data[0] &= 0xf;
	wbits = devpriv->do_bits;
	/*  zero bits that have been masked */
	wbits &= ~data[0];
	/*  set masked bits */
	wbits |= data[0] & data[1];
	devpriv->do_bits = wbits;
	data[1] = wbits;

	outb(devpriv->do_bits, dev->iobase + DAS16M1_DIO);

	return 2;
}