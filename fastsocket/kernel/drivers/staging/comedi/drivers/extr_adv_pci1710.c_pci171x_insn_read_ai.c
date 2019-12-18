#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_4__ {unsigned int* act_chanlist; int /*<<< orphan*/  CntrlReg; } ;
struct TYPE_3__ {scalar_t__ cardtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  Control_CNT0 ; 
 int /*<<< orphan*/  Control_SW ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int ETIME ; 
 scalar_t__ PCI171x_AD_DATA ; 
 scalar_t__ PCI171x_CLRFIFO ; 
 scalar_t__ PCI171x_CLRINT ; 
 scalar_t__ PCI171x_CONTROL ; 
 scalar_t__ PCI171x_SOFTTRG ; 
 scalar_t__ PCI171x_STATUS ; 
 int Status_FE ; 
 scalar_t__ TYPE_PCI1713 ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_2__* devpriv ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setup_channel_list (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pci171x_insn_read_ai(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	int n, timeout;
#ifdef PCI171x_PARANOIDCHECK
	unsigned int idata;
#endif

	DPRINTK("adv_pci1710 EDBG: BGN: pci171x_insn_read_ai(...)\n");
	devpriv->CntrlReg &= Control_CNT0;
	devpriv->CntrlReg |= Control_SW;	/*  set software trigger */
	outw(devpriv->CntrlReg, dev->iobase + PCI171x_CONTROL);
	outb(0, dev->iobase + PCI171x_CLRFIFO);
	outb(0, dev->iobase + PCI171x_CLRINT);

	setup_channel_list(dev, s, &insn->chanspec, 1, 1);

	DPRINTK("adv_pci1710 A ST=%4x IO=%x\n",
		inw(dev->iobase + PCI171x_STATUS),
		dev->iobase + PCI171x_STATUS);
	for (n = 0; n < insn->n; n++) {
		outw(0, dev->iobase + PCI171x_SOFTTRG);	/* start conversion */
		DPRINTK("adv_pci1710 B n=%d ST=%4x\n", n,
			inw(dev->iobase + PCI171x_STATUS));
		/* udelay(1); */
		DPRINTK("adv_pci1710 C n=%d ST=%4x\n", n,
			inw(dev->iobase + PCI171x_STATUS));
		timeout = 100;
		while (timeout--) {
			if (!(inw(dev->iobase + PCI171x_STATUS) & Status_FE))
				goto conv_finish;
			if (!(timeout % 10))
				DPRINTK("adv_pci1710 D n=%d tm=%d ST=%4x\n", n,
					timeout,
					inw(dev->iobase + PCI171x_STATUS));
		}
		comedi_error(dev, "A/D insn timeout");
		outb(0, dev->iobase + PCI171x_CLRFIFO);
		outb(0, dev->iobase + PCI171x_CLRINT);
		data[n] = 0;
		DPRINTK
		    ("adv_pci1710 EDBG: END: pci171x_insn_read_ai(...) n=%d\n",
		     n);
		return -ETIME;

conv_finish:
#ifdef PCI171x_PARANOIDCHECK
		idata = inw(dev->iobase + PCI171x_AD_DATA);
		if (this_board->cardtype != TYPE_PCI1713)
			if ((idata & 0xf000) != devpriv->act_chanlist[0]) {
				comedi_error(dev, "A/D insn data droput!");
				return -ETIME;
			}
		data[n] = idata & 0x0fff;
#else
		data[n] = inw(dev->iobase + PCI171x_AD_DATA) & 0x0fff;
#endif

	}

	outb(0, dev->iobase + PCI171x_CLRFIFO);
	outb(0, dev->iobase + PCI171x_CLRINT);

	DPRINTK("adv_pci1710 EDBG: END: pci171x_insn_read_ai(...) n=%d\n", n);
	return n;
}