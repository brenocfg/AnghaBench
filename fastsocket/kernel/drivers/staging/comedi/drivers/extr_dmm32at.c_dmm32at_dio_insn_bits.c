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
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int dio_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMM32AT_CNTRL ; 
 int /*<<< orphan*/  DMM32AT_DIOA ; 
 unsigned char DMM32AT_DIOACC ; 
 int /*<<< orphan*/  DMM32AT_DIOB ; 
 int /*<<< orphan*/  DMM32AT_DIOC ; 
 int DMM32AT_DIRA ; 
 int DMM32AT_DIRB ; 
 int DMM32AT_DIRCH ; 
 int DMM32AT_DIRCL ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int dmm_inb (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmm_outb (struct comedi_device*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int dmm32at_dio_insn_bits(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	unsigned char diobits;

	if (insn->n != 2)
		return -EINVAL;

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */
	if (data[0]) {
		s->state &= ~data[0];
		s->state |= data[0] & data[1];
		/* Write out the new digital output lines */
		/* outw(s->state,dev->iobase + DMM32AT_DIO); */
	}

	/* get access to the DIO regs */
	dmm_outb(dev, DMM32AT_CNTRL, DMM32AT_DIOACC);

	/* if either part of dio is set for output */
	if (((devpriv->dio_config & DMM32AT_DIRCL) == 0) ||
	    ((devpriv->dio_config & DMM32AT_DIRCH) == 0)) {
		diobits = (s->state & 0x00ff0000) >> 16;
		dmm_outb(dev, DMM32AT_DIOC, diobits);
	}
	if ((devpriv->dio_config & DMM32AT_DIRB) == 0) {
		diobits = (s->state & 0x0000ff00) >> 8;
		dmm_outb(dev, DMM32AT_DIOB, diobits);
	}
	if ((devpriv->dio_config & DMM32AT_DIRA) == 0) {
		diobits = (s->state & 0x000000ff);
		dmm_outb(dev, DMM32AT_DIOA, diobits);
	}

	/* now read the state back in */
	s->state = dmm_inb(dev, DMM32AT_DIOC);
	s->state <<= 8;
	s->state |= dmm_inb(dev, DMM32AT_DIOB);
	s->state <<= 8;
	s->state |= dmm_inb(dev, DMM32AT_DIOA);
	data[1] = s->state;

	/* on return, data[1] contains the value of the digital
	 * input and output lines. */
	/* data[1]=inw(dev->iobase + DMM32AT_DIO); */
	/* or we could just return the software copy of the output values if
	 * it was a purely digital output subdevice */
	/* data[1]=s->state; */

	return 2;
}