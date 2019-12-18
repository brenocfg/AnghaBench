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
struct TYPE_2__ {int ai_gain; } ;
union pci20xxx_subdev_private {scalar_t__ iobase; TYPE_1__ pci20341; } ;
struct comedi_subdevice {union pci20xxx_subdev_private* private; } ;
struct comedi_insn {unsigned int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int /*<<< orphan*/  minor; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ PCI20341_CC_RESET ; 
 scalar_t__ PCI20341_CHAN_LIST ; 
 scalar_t__ PCI20341_CHAN_RESET ; 
 int PCI20341_DAISY_CHAIN ; 
 scalar_t__ PCI20341_LCHAN_ADDR_REG ; 
 scalar_t__ PCI20341_LDATA ; 
 int PCI20341_MUX ; 
 scalar_t__ PCI20341_SOFT_PACER ; 
 scalar_t__ PCI20341_STATUS_REG ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned int) ; 
 void* readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pci20341_insn_read(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn, unsigned int *data)
{
	union pci20xxx_subdev_private *sdp = s->private;
	unsigned int i = 0, j = 0;
	int lo, hi;
	unsigned char eoc;	/* end of conversion */
	unsigned int clb;	/* channel list byte */
	unsigned int boarddata;

	writeb(1, sdp->iobase + PCI20341_LCHAN_ADDR_REG);	/* write number of input channels */
	clb = PCI20341_DAISY_CHAIN | PCI20341_MUX | (sdp->pci20341.ai_gain << 3)
	    | CR_CHAN(insn->chanspec);
	writeb(clb, sdp->iobase + PCI20341_CHAN_LIST);
	writeb(0x00, sdp->iobase + PCI20341_CC_RESET);	/* reset settling time counter and trigger delay counter */
	writeb(0x00, sdp->iobase + PCI20341_CHAN_RESET);

	/* generate Pacer */

	for (i = 0; i < insn->n; i++) {
		/* data polling isn't the niciest way to get the data, I know,
		 * but there are only 6 cycles (mean) and it is easier than
		 * the whole interrupt stuff
		 */
		j = 0;
		readb(sdp->iobase + PCI20341_SOFT_PACER);	/* generate Pacer */
		eoc = readb(sdp->iobase + PCI20341_STATUS_REG);
		while ((eoc < 0x80) && j < 100) {	/* poll Interrupt Flag */
			j++;
			eoc = readb(sdp->iobase + PCI20341_STATUS_REG);
		}
		if (j >= 100) {
			printk
			    ("comedi%d:  pci20xxx: AI interrupt channel %i polling exit !\n",
			     dev->minor, i);
			return -EINVAL;
		}
		lo = readb(sdp->iobase + PCI20341_LDATA);
		hi = readb(sdp->iobase + PCI20341_LDATA + 1);
		boarddata = lo + 0x100 * hi;
		data[i] = (short)((boarddata + 0x8000) & 0xffff);	/* board-data -> comedi-data */
	}

	return i;
}