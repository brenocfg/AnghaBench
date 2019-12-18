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
struct comedi_subdevice {unsigned int io_bits; unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_3_reg; int /*<<< orphan*/  port_2_reg; int /*<<< orphan*/  port_1_reg; int /*<<< orphan*/  port_0_reg; } ;
struct TYPE_4__ {TYPE_1__ dio_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_PDEBUG (char*) ; 
 int EINVAL ; 
 int EIO ; 
 TYPE_2__* info ; 
 int me4000_inl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me4000_outl (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int me4000_dio_insn_bits(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{

	CALL_PDEBUG("In me4000_dio_insn_bits()\n");

	/* Length of data must be 2 (mask and new data, see below) */
	if (insn->n == 0)
		return 0;

	if (insn->n != 2) {
		printk
		    ("comedi%d: me4000: me4000_dio_insn_bits(): Invalid instruction length\n",
		     dev->minor);
		return -EINVAL;
	}

	/*
	 * The insn data consists of a mask in data[0] and the new data
	 * in data[1]. The mask defines which bits we are concerning about.
	 * The new data must be anded with the mask.
	 * Each channel corresponds to a bit.
	 */
	if (data[0]) {
		/* Check if requested ports are configured for output */
		if ((s->io_bits & data[0]) != data[0])
			return -EIO;

		s->state &= ~data[0];
		s->state |= data[0] & data[1];

		/* Write out the new digital output lines */
		me4000_outl(dev, (s->state >> 0) & 0xFF,
			    info->dio_context.port_0_reg);
		me4000_outl(dev, (s->state >> 8) & 0xFF,
			    info->dio_context.port_1_reg);
		me4000_outl(dev, (s->state >> 16) & 0xFF,
			    info->dio_context.port_2_reg);
		me4000_outl(dev, (s->state >> 24) & 0xFF,
			    info->dio_context.port_3_reg);
	}

	/* On return, data[1] contains the value of
	   the digital input and output lines. */
	data[1] =
	    ((me4000_inl(dev, info->dio_context.port_0_reg) & 0xFF) << 0) |
	    ((me4000_inl(dev, info->dio_context.port_1_reg) & 0xFF) << 8) |
	    ((me4000_inl(dev, info->dio_context.port_2_reg) & 0xFF) << 16) |
	    ((me4000_inl(dev, info->dio_context.port_3_reg) & 0xFF) << 24);

	return 2;
}