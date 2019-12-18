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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int exttrg_users; int IntControlReg; scalar_t__ iobase_a; } ;

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_INTCSR ; 
 int Int_DTrg ; 
 scalar_t__ PCI9118_INTCTRL ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static int pci9118_exttrg_del(struct comedi_device *dev, unsigned char source)
{
	if (source > 3)
		return -1;	/*  incorrect source */
	devpriv->exttrg_users &= ~(1 << source);
	if (!devpriv->exttrg_users) {	/*  shutdown ext trg intterrupts */
		devpriv->IntControlReg &= ~Int_DTrg;
		if (!devpriv->IntControlReg)	/*  all IRQ disabled */
			outl(inl(devpriv->iobase_a + AMCC_OP_REG_INTCSR) & (~0x00001f00), devpriv->iobase_a + AMCC_OP_REG_INTCSR);	/*  disable int in AMCC */
		outl(devpriv->IntControlReg, dev->iobase + PCI9118_INTCTRL);
	}
	return 0;
}