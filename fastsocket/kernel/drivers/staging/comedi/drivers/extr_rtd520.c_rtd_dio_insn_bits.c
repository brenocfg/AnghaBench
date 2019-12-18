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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RtdDio0Read (struct comedi_device*) ; 
 int /*<<< orphan*/  RtdDio0Write (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int rtd_dio_insn_bits(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	if (insn->n != 2)
		return -EINVAL;

	/* The insn data is a mask in data[0] and the new data
	 * in data[1], each channel cooresponding to a bit. */
	if (data[0]) {
		s->state &= ~data[0];
		s->state |= data[0] & data[1];

		/* Write out the new digital output lines */
		RtdDio0Write(dev, s->state);
	}
	/* on return, data[1] contains the value of the digital
	 * input lines. */
	data[1] = RtdDio0Read(dev);

	/*DPRINTK("rtd520:port_0 wrote: 0x%x read: 0x%x\n", s->state, data[1]); */

	return 2;
}