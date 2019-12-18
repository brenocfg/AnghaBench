#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* iobase; } ;
struct TYPE_4__ {void* iobase; } ;
union pci20xxx_subdev_private {TYPE_2__ pci20341; TYPE_1__ pci20006; } ;
struct pci20xxx_private {int dummy; } ;
struct comedi_subdevice {int /*<<< orphan*/  type; union pci20xxx_subdev_private* private; } ;
struct comedi_device {char* board_name; struct comedi_subdevice* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {scalar_t__* options; } ;
struct TYPE_6__ {void* ioaddr; union pci20xxx_subdev_private* subdev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
 int EINVAL ; 
 int PCI20000_ID ; 
 int PCI20000_MODULES ; 
 unsigned char PCI20000_OFFSET ; 
#define  PCI20006_ID 130 
#define  PCI20341_ID 129 
#define  PCI20xxx_EMPTY_ID 128 
 int alloc_private (struct comedi_device*,int) ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  pci20006_init (struct comedi_device*,struct comedi_subdevice*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci20341_init (struct comedi_device*,struct comedi_subdevice*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci20xxx_dio_init (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int readb (void*) ; 

__attribute__((used)) static int pci20xxx_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	unsigned char i;
	int ret;
	int id;
	struct comedi_subdevice *s;
	union pci20xxx_subdev_private *sdp;

	ret = alloc_subdevices(dev, 1 + PCI20000_MODULES);
	if (ret < 0)
		return ret;

	ret = alloc_private(dev, sizeof(struct pci20xxx_private));
	if (ret < 0)
		return ret;

	devpriv->ioaddr = (void *)(unsigned long)it->options[0];
	dev->board_name = "pci20kc";

	/* Check PCI-20001 C-2A Carrier Board ID */
	if ((readb(devpriv->ioaddr) & PCI20000_ID) != PCI20000_ID) {
		printk("comedi%d: ii_pci20kc", dev->minor);
		printk
		    (" PCI-20001 C-2A Carrier Board at base=0x%p not found !\n",
		     devpriv->ioaddr);
		return -EINVAL;
	}
	printk("comedi%d:\n", dev->minor);
	printk("ii_pci20kc: PCI-20001 C-2A at base=0x%p\n", devpriv->ioaddr);

	for (i = 0; i < PCI20000_MODULES; i++) {
		s = dev->subdevices + i;
		id = readb(devpriv->ioaddr + (i + 1) * PCI20000_OFFSET);
		s->private = devpriv->subdev_private + i;
		sdp = s->private;
		switch (id) {
		case PCI20006_ID:
			sdp->pci20006.iobase =
			    devpriv->ioaddr + (i + 1) * PCI20000_OFFSET;
			pci20006_init(dev, s, it->options[2 * i + 2],
				      it->options[2 * i + 3]);
			printk("comedi%d: ii_pci20kc", dev->minor);
			printk(" PCI-20006 module in slot %d \n", i + 1);
			break;
		case PCI20341_ID:
			sdp->pci20341.iobase =
			    devpriv->ioaddr + (i + 1) * PCI20000_OFFSET;
			pci20341_init(dev, s, it->options[2 * i + 2],
				      it->options[2 * i + 3]);
			printk("comedi%d: ii_pci20kc", dev->minor);
			printk(" PCI-20341 module in slot %d \n", i + 1);
			break;
		default:
			printk
			    ("ii_pci20kc: unknown module code 0x%02x in slot %d: module disabled\n",
			     id, i);
			/* fall through */
		case PCI20xxx_EMPTY_ID:
			s->type = COMEDI_SUBD_UNUSED;
			break;
		}
	}

	/* initialize struct pci20xxx_private */
	pci20xxx_dio_init(dev, dev->subdevices + PCI20000_MODULES);

	return 1;
}