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
typedef  int u8 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_INPUT ; 
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSCDR ; 
 int /*<<< orphan*/  CSCIR ; 
 int EINVAL ; 
#define  INSN_CONFIG_DIO_INPUT 130 
#define  INSN_CONFIG_DIO_OUTPUT 129 
#define  INSN_CONFIG_DIO_QUERY 128 
 int PAMR ; 
 int PBMR ; 
 int PCMR ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnp_dio_insn_config(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{

	u8 register_buffer;

	int chan = CR_CHAN(insn->chanspec);	/* reduces chanspec to lower 16 bits */

	switch (data[0]) {
	case INSN_CONFIG_DIO_OUTPUT:
	case INSN_CONFIG_DIO_INPUT:
		break;
	case INSN_CONFIG_DIO_QUERY:
		data[1] =
		    (inb(CSCDR) & (1 << chan)) ? COMEDI_OUTPUT : COMEDI_INPUT;
		return insn->n;
		break;
	default:
		return -EINVAL;
		break;
	}
	/* Test: which port does the channel belong to?                            */

	/* We have to pay attention with port C: this is the meaning of PCMR:      */
	/* Bit in PCMR:              7 6 5 4 3 2 1 0                               */
	/* Corresponding port C pin: d 3 d 2 d 1 d 0   d= don't touch              */

	if ((chan >= 0) && (chan <= 7)) {
		/* this is port A */
		outb(PAMR, CSCIR);
	} else if ((chan >= 8) && (chan <= 15)) {
		/* this is port B */
		chan -= 8;
		outb(PBMR, CSCIR);
	} else if ((chan >= 16) && (chan <= 19)) {
		/* this is port C; multiplication with 2 brings bits into correct        */
		/* position for PCMR!                                                    */
		chan -= 16;
		chan *= 2;
		outb(PCMR, CSCIR);
	} else {
		return -EINVAL;
	}

	/* read 'old' direction of the port and set bits (out=1, in=0)             */
	register_buffer = inb(CSCDR);
	if (data[0] == COMEDI_OUTPUT) {
		register_buffer |= (1 << chan);
	} else {
		register_buffer &= ~(1 << chan);
	}
	outb(register_buffer, CSCDR);

	return 1;

}