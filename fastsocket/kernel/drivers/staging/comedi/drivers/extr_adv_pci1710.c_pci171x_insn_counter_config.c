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
typedef  int /*<<< orphan*/  uint ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {unsigned int cnt0_write_wait; int /*<<< orphan*/  CntrlReg; } ;

/* Variables and functions */
 int /*<<< orphan*/  Control_CNT0 ; 
 int /*<<< orphan*/  Counter_BCD ; 
 int /*<<< orphan*/  Counter_M0 ; 
 int /*<<< orphan*/  Counter_M1 ; 
 int /*<<< orphan*/  Counter_M2 ; 
 int /*<<< orphan*/  Counter_RW0 ; 
 int /*<<< orphan*/  Counter_RW1 ; 
 scalar_t__ PCI171x_CNTCTRL ; 
 scalar_t__ PCI171x_CONTROL ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pci171x_insn_counter_config(struct comedi_device *dev,
				       struct comedi_subdevice *s,
				       struct comedi_insn *insn,
				       unsigned int *data)
{
#ifdef unused
	/* This doesn't work like a normal Comedi counter config */
	uint ccntrl = 0;

	devpriv->cnt0_write_wait = data[0] & 0x20;

	/* internal or external clock? */
	if (!(data[0] & 0x10)) {	/* internal */
		devpriv->CntrlReg &= ~Control_CNT0;
	} else {
		devpriv->CntrlReg |= Control_CNT0;
	}
	outw(devpriv->CntrlReg, dev->iobase + PCI171x_CONTROL);

	if (data[0] & 0x01)
		ccntrl |= Counter_M0;
	if (data[0] & 0x02)
		ccntrl |= Counter_M1;
	if (data[0] & 0x04)
		ccntrl |= Counter_M2;
	if (data[0] & 0x08)
		ccntrl |= Counter_BCD;
	ccntrl |= Counter_RW0;	/* set read/write mode */
	ccntrl |= Counter_RW1;
	outw(ccntrl, dev->iobase + PCI171x_CNTCTRL);
#endif

	return 1;
}