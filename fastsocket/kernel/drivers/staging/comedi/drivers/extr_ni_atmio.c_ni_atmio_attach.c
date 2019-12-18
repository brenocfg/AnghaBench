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
struct pnp_dev {int dummy; } ;
struct comedi_device {unsigned long iobase; unsigned int irq; int /*<<< orphan*/  board_name; scalar_t__ board_ptr; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct pnp_dev* isapnp_dev; int /*<<< orphan*/ * stc_readl; int /*<<< orphan*/ * stc_writel; int /*<<< orphan*/ * stc_readw; int /*<<< orphan*/ * stc_writew; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NI_E_IRQ_FLAGS ; 
 int /*<<< orphan*/  NI_SIZE ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  inw (int) ; 
 int ni_E_init (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  ni_E_interrupt ; 
 int ni_alloc_private (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_atmio_win_in ; 
 int /*<<< orphan*/  ni_atmio_win_out ; 
 scalar_t__ ni_boards ; 
 int ni_getboardtype (struct comedi_device*) ; 
 int* ni_irqpin ; 
 int ni_isapnp_find_board (struct pnp_dev**) ; 
 unsigned int pnp_irq (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pnp_port_start (struct pnp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct comedi_device*) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_in2 ; 
 int /*<<< orphan*/  win_out2 ; 

__attribute__((used)) static int ni_atmio_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	struct pnp_dev *isapnp_dev;
	int ret;
	unsigned long iobase;
	int board;
	unsigned int irq;

	/* allocate private area */
	ret = ni_alloc_private(dev);
	if (ret < 0)
		return ret;

	devpriv->stc_writew = &ni_atmio_win_out;
	devpriv->stc_readw = &ni_atmio_win_in;
	devpriv->stc_writel = &win_out2;
	devpriv->stc_readl = &win_in2;

	iobase = it->options[0];
	irq = it->options[1];
	isapnp_dev = NULL;
	if (iobase == 0) {
		ret = ni_isapnp_find_board(&isapnp_dev);
		if (ret < 0)
			return ret;

		iobase = pnp_port_start(isapnp_dev, 0);
		irq = pnp_irq(isapnp_dev, 0);
		devpriv->isapnp_dev = isapnp_dev;
	}

	/* reserve our I/O region */

	printk("comedi%d: ni_atmio: 0x%04lx", dev->minor, iobase);
	if (!request_region(iobase, NI_SIZE, "ni_atmio")) {
		printk(" I/O port conflict\n");
		return -EIO;
	}

	dev->iobase = iobase;

#ifdef DEBUG
	/* board existence sanity check */
	{
		int i;

		printk(" board fingerprint:");
		for (i = 0; i < 16; i += 2) {
			printk(" %04x %02x", inw(dev->iobase + i),
			       inb(dev->iobase + i + 1));
		}
	}
#endif

	/* get board type */

	board = ni_getboardtype(dev);
	if (board < 0)
		return -EIO;

	dev->board_ptr = ni_boards + board;

	printk(" %s", boardtype.name);
	dev->board_name = boardtype.name;

	/* irq stuff */

	if (irq != 0) {
		if (irq > 15 || ni_irqpin[irq] == -1) {
			printk(" invalid irq %u\n", irq);
			return -EINVAL;
		}
		printk(" ( irq = %u )", irq);
		ret = request_irq(irq, ni_E_interrupt, NI_E_IRQ_FLAGS,
				  "ni_atmio", dev);

		if (ret < 0) {
			printk(" irq not available\n");
			return -EINVAL;
		}
		dev->irq = irq;
	}

	/* generic E series stuff in ni_mio_common.c */

	ret = ni_E_init(dev, it);
	if (ret < 0) {
		return ret;
	}

	return 0;
}