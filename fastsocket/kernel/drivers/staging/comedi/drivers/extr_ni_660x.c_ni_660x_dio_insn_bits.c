#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIO32Input ; 
 int /*<<< orphan*/  DIO32Output ; 
 unsigned int ni_660x_read_register (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_660x_write_register (struct comedi_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_660x_dio_insn_bits(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn, unsigned int *data)
{
	unsigned base_bitfield_channel = CR_CHAN(insn->chanspec);

	/*  Check if we have to write some bits */
	if (data[0]) {
		s->state &= ~(data[0] << base_bitfield_channel);
		s->state |= (data[0] & data[1]) << base_bitfield_channel;
		/* Write out the new digital output lines */
		ni_660x_write_register(dev, 0, s->state, DIO32Output);
	}
	/* on return, data[1] contains the value of the digital
	 * input and output lines. */
	data[1] =
	    (ni_660x_read_register(dev, 0,
				   DIO32Input) >> base_bitfield_channel);
	return 2;
}