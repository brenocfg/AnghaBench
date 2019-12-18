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
struct comedi_subdevice {unsigned int io_bits; unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  RDDIn; int /*<<< orphan*/  WRDOut; } ;

/* Variables and functions */
 unsigned int DEBIread (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int EINVAL ; 
 int EIO ; 
 TYPE_1__* diopriv ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s626_dio_insn_bits(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{

	/* Length of data must be 2 (mask and new data, see below) */
	if (insn->n == 0)
		return 0;

	if (insn->n != 2) {
		printk
		    ("comedi%d: s626: s626_dio_insn_bits(): Invalid instruction length\n",
		     dev->minor);
		return -EINVAL;
	}

	/*
	 * The insn data consists of a mask in data[0] and the new data in
	 * data[1]. The mask defines which bits we are concerning about.
	 * The new data must be anded with the mask.  Each channel
	 * corresponds to a bit.
	 */
	if (data[0]) {
		/* Check if requested ports are configured for output */
		if ((s->io_bits & data[0]) != data[0])
			return -EIO;

		s->state &= ~data[0];
		s->state |= data[0] & data[1];

		/* Write out the new digital output lines */

		DEBIwrite(dev, diopriv->WRDOut, s->state);
	}
	data[1] = DEBIread(dev, diopriv->RDDIn);

	return 2;
}