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
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ APCI3120_RD_STATUS ; 
 TYPE_1__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 

int i_APCI3120_InsnBitsDigitalInput(struct comedi_device *dev, struct comedi_subdevice *s,
	struct comedi_insn *insn, unsigned int *data)
{
	unsigned int ui_TmpValue;
	ui_TmpValue = (unsigned int) inw(devpriv->iobase + APCI3120_RD_STATUS);
	/*****	state of 4 channels  in the 11, 10, 9, 8   bits of status reg
			rotated right 8 times to bring them to last four bits
			ANDed with oxf for  value.
	*****/

	*data = (ui_TmpValue >> 8) & 0xf;
	/* this_board->i_hwdrv_InsnBitsDigitalInput(dev,data); */
	return insn->n;
}