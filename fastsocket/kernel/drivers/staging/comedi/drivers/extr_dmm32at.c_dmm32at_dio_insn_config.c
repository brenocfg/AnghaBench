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
struct TYPE_2__ {unsigned char dio_config; } ;

/* Variables and functions */
 unsigned int COMEDI_OUTPUT ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMM32AT_CNTRL ; 
 unsigned char DMM32AT_DIOACC ; 
 int /*<<< orphan*/  DMM32AT_DIOCONF ; 
 unsigned char DMM32AT_DIRA ; 
 unsigned char DMM32AT_DIRB ; 
 unsigned char DMM32AT_DIRCH ; 
 unsigned char DMM32AT_DIRCL ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  dmm_outb (struct comedi_device*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int dmm32at_dio_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn, unsigned int *data)
{
	unsigned char chanbit;
	int chan = CR_CHAN(insn->chanspec);

	if (insn->n != 1)
		return -EINVAL;

	if (chan < 8)
		chanbit = DMM32AT_DIRA;
	else if (chan < 16)
		chanbit = DMM32AT_DIRB;
	else if (chan < 20)
		chanbit = DMM32AT_DIRCL;
	else
		chanbit = DMM32AT_DIRCH;

	/* The input or output configuration of each digital line is
	 * configured by a special insn_config instruction.  chanspec
	 * contains the channel to be changed, and data[0] contains the
	 * value COMEDI_INPUT or COMEDI_OUTPUT. */

	/* if output clear the bit, otherwise set it */
	if (data[0] == COMEDI_OUTPUT) {
		devpriv->dio_config &= ~chanbit;
	} else {
		devpriv->dio_config |= chanbit;
	}
	/* get access to the DIO regs */
	dmm_outb(dev, DMM32AT_CNTRL, DMM32AT_DIOACC);
	/* set the DIO's to the new configuration setting */
	dmm_outb(dev, DMM32AT_DIOCONF, devpriv->dio_config);

	return 1;
}