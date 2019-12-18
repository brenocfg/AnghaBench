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
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3120_RD_STATUS ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 

int i_APCI3120_InsnReadDigitalInput(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned int ui_Chan, ui_TmpValue;

	ui_Chan = CR_CHAN(insn->chanspec);	/*  channel specified */

	/* this_board->i_hwdrv_InsnReadDigitalInput(dev,ui_Chan,data); */
	if (ui_Chan >= 0 && ui_Chan <= 3) {
		ui_TmpValue = (unsigned int) inw(devpriv->iobase + APCI3120_RD_STATUS);

/*
 * since only 1 channel reqd to bring it to last bit it is rotated 8
 * +(chan - 1) times then ANDed with 1 for last bit.
 */
		*data = (ui_TmpValue >> (ui_Chan + 8)) & 1;
		/* return 0; */
	} else {
		/*       comedi_error(dev," chan spec wrong"); */
		return -EINVAL;	/*  "sorry channel spec wrong " */
	}
	return insn->n;

}