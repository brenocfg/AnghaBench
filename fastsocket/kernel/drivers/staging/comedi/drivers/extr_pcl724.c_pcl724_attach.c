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
struct comedi_device {unsigned long iobase; unsigned int irq; int n_subdevices; scalar_t__ subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_2__ {unsigned int io_range; int IRQbits; int numofports; scalar_t__ is_pet48; scalar_t__ can_have96; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int PCL722_96_SIZE ; 
 int SIZE_8255 ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  interrupt_pcl724 ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct comedi_device*) ; 
 int /*<<< orphan*/  request_region (unsigned long,unsigned int,char*) ; 
 int /*<<< orphan*/  subdev_8255_cb ; 
 int /*<<< orphan*/  subdev_8255_init (struct comedi_device*,scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  subdev_8255mapped_cb ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pcl724_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	unsigned long iobase;
	unsigned int iorange;
	int ret, i, n_subdevices;
#ifdef PCL724_IRQ
	unsigned int irq;
#endif

	iobase = it->options[0];
	iorange = this_board->io_range;
	if ((this_board->can_have96) && ((it->options[1] == 1)
					 || (it->options[1] == 96)))
		iorange = PCL722_96_SIZE;	/*  PCL-724 in 96 DIO configuration */
	printk("comedi%d: pcl724: board=%s, 0x%03lx ", dev->minor,
	       this_board->name, iobase);
	if (!request_region(iobase, iorange, "pcl724")) {
		printk("I/O port conflict\n");
		return -EIO;
	}

	dev->iobase = iobase;

	dev->board_name = this_board->name;

#ifdef PCL724_IRQ
	irq = 0;
	if (this_board->IRQbits != 0) {	/* board support IRQ */
		irq = it->options[1];
		if (irq) {	/* we want to use IRQ */
			if (((1 << irq) & this_board->IRQbits) == 0) {
				printk
				    (", IRQ %u is out of allowed range, DISABLING IT",
				     irq);
				irq = 0;	/* Bad IRQ */
			} else {
				if (request_irq
				    (irq, interrupt_pcl724, 0, "pcl724", dev)) {
					printk
					    (", unable to allocate IRQ %u, DISABLING IT",
					     irq);
					irq = 0;	/* Can't use IRQ */
				} else {
					printk(", irq=%u", irq);
				}
			}
		}
	}

	dev->irq = irq;
#endif

	printk("\n");

	n_subdevices = this_board->numofports;
	if ((this_board->can_have96) && ((it->options[1] == 1)
					 || (it->options[1] == 96)))
		n_subdevices = 4;	/*  PCL-724 in 96 DIO configuration */

	ret = alloc_subdevices(dev, n_subdevices);
	if (ret < 0)
		return ret;

	for (i = 0; i < dev->n_subdevices; i++) {
		if (this_board->is_pet48) {
			subdev_8255_init(dev, dev->subdevices + i,
					 subdev_8255mapped_cb,
					 (unsigned long)(dev->iobase +
							 i * 0x1000));
		} else
			subdev_8255_init(dev, dev->subdevices + i,
					 subdev_8255_cb,
					 (unsigned long)(dev->iobase +
							 SIZE_8255 * i));
	};

	return 0;
}