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
struct comedi_subdevice {int io_bits; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int) ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 
 int /*<<< orphan*/  RtdDio0CtrlWrite (struct comedi_device*,int) ; 
 int /*<<< orphan*/  RtdDioStatusWrite (struct comedi_device*,int) ; 

__attribute__((used)) static int rtd_dio_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	int chan = CR_CHAN(insn->chanspec);

	/* The input or output configuration of each digital line is
	 * configured by a special insn_config instruction.  chanspec
	 * contains the channel to be changed, and data[0] contains the
	 * value COMEDI_INPUT or COMEDI_OUTPUT. */
	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
		s->io_bits |= 1 << chan;	/* 1 means Out */
		break;
	case INSN_CONFIG_DIO_INPUT:
		s->io_bits &= ~(1 << chan);
		break;
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    (s->io_bits & (1 << chan)) ? COMEDI_OUTPUT : COMEDI_INPUT;
		return insn->n;
		break;
	default:
		return -EINVAL;
	}

	DPRINTK("rtd520: port_0_direction=0x%x (1 means out)\n", s->io_bits);
	/* TODO support digital match interrupts and strobes */
	RtdDioStatusWrite(dev, 0x01);	/* make Dio0Ctrl point to direction */
	RtdDio0CtrlWrite(dev, s->io_bits);	/* set direction 1 means Out */
	RtdDioStatusWrite(dev, 0);	/* make Dio0Ctrl clear interrupts */

	/* port1 can only be all input or all output */

	/* there are also 2 user input lines and 2 user output lines */

	return 1;
}