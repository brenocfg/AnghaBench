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
struct TYPE_2__ {unsigned int* last_data; } ;
union pci20xxx_subdev_private {scalar_t__ iobase; TYPE_1__ pci20006; } ;
struct comedi_subdevice {union pci20xxx_subdev_private* private; } ;
struct comedi_insn {int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ PCI20006_LCHAN0 ; 
 scalar_t__ PCI20006_LCHAN1 ; 
 scalar_t__ PCI20006_STROBE0 ; 
 scalar_t__ PCI20006_STROBE1 ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pci20006_insn_write(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn, unsigned int *data)
{
	union pci20xxx_subdev_private *sdp = s->private;
	int hi, lo;
	unsigned int boarddata;

	sdp->pci20006.last_data[CR_CHAN(insn->chanspec)] = data[0];
	boarddata = (((unsigned int)data[0] + 0x8000) & 0xffff);	/* comedi-data -> board-data */
	lo = (boarddata & 0xff);
	hi = ((boarddata >> 8) & 0xff);

	switch (CR_CHAN(insn->chanspec)) {
	case 0:
		writeb(lo, sdp->iobase + PCI20006_LCHAN0);
		writeb(hi, sdp->iobase + PCI20006_LCHAN0 + 1);
		writeb(0x00, sdp->iobase + PCI20006_STROBE0);
		break;
	case 1:
		writeb(lo, sdp->iobase + PCI20006_LCHAN1);
		writeb(hi, sdp->iobase + PCI20006_LCHAN1 + 1);
		writeb(0x00, sdp->iobase + PCI20006_STROBE1);
		break;
	default:
		printk(" comedi%d: pci20xxx: ao channel Error!\n", dev->minor);
		return -EINVAL;
	}

	return 1;
}