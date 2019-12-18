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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_InterruptMode; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3501_ANALOG_OUTPUT ; 
 scalar_t__ APCI3501_AO_PROG ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE1 ; 
 TYPE_1__* devpriv ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3501_WriteAnalogOutput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ul_Command1 = 0, ul_Channel_no, ul_Polarity, ul_DAC_Ready = 0;;

	ul_Channel_no = CR_CHAN(insn->chanspec);

	if (devpriv->b_InterruptMode == MODE1) {
		ul_Polarity = 0x80000000;
		if ((*data < 0) || (*data > 16384)) {
			printk("\nIn WriteAnalogOutput :: Not Valid Data\n");
		}

	}			/*  end if(devpriv->b_InterruptMode==MODE1) */
	else {
		ul_Polarity = 0;
		if ((*data < 0) || (*data > 8192)) {
			printk("\nIn WriteAnalogOutput :: Not Valid Data\n");
		}

	}			/*  end else */

	if ((ul_Channel_no < 0) || (ul_Channel_no > 7)) {
		printk("\nIn WriteAnalogOutput :: Not Valid Channel\n");
	}			/*  end if((ul_Channel_no<0)||(ul_Channel_no>7)) */

	ul_DAC_Ready = inl(devpriv->iobase + APCI3501_ANALOG_OUTPUT);

	while (ul_DAC_Ready == 0) {
		ul_DAC_Ready = inl(devpriv->iobase + APCI3501_ANALOG_OUTPUT);
		ul_DAC_Ready = (ul_DAC_Ready >> 8) & 1;
	}

	if (ul_DAC_Ready) {
/* Output the Value on the output channels. */
		ul_Command1 =
			(unsigned int) ((unsigned int) (ul_Channel_no & 0xFF) |
			(unsigned int) ((*data << 0x8) & 0x7FFFFF00L) |
			(unsigned int) (ul_Polarity));
		outl(ul_Command1,
			devpriv->iobase + APCI3501_ANALOG_OUTPUT +
			APCI3501_AO_PROG);
	}

	return insn->n;
}