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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI171x_CNT0 ; 
 scalar_t__ PCI171x_CNTCTRL ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pci171x_insn_counter_read(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int msb, lsb, ccntrl;
	int i;

	ccntrl = 0xD2;		/* count only */
	for (i = 0; i < insn->n; i++) {
		outw(ccntrl, dev->iobase + PCI171x_CNTCTRL);

		lsb = inw(dev->iobase + PCI171x_CNT0) & 0xFF;
		msb = inw(dev->iobase + PCI171x_CNT0) & 0xFF;

		data[0] = lsb | (msb << 8);
	}

	return insn->n;
}