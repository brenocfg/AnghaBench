#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int AssignedIRQ; } ;
struct TYPE_6__ {int /*<<< orphan*/  BasePort1; } ;
struct pcmcia_device {TYPE_2__ irq; TYPE_1__ io; } ;
struct comedi_device {unsigned int irq; int /*<<< orphan*/  board_name; scalar_t__ board_ptr; int /*<<< orphan*/  iobase; TYPE_3__* driver; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/ * stc_readl; int /*<<< orphan*/ * stc_writel; int /*<<< orphan*/ * stc_readw; int /*<<< orphan*/ * stc_writew; } ;
struct TYPE_8__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct comedi_device*,struct comedi_devconfig*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  NI_E_IRQ_FLAGS ; 
 TYPE_5__ boardtype ; 
 struct pcmcia_device* cur_dev ; 
 TYPE_4__* devpriv ; 
 TYPE_3__ driver_ni_mio_cs ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mio_cs_win_in ; 
 int /*<<< orphan*/  mio_cs_win_out ; 
 int ni_E_init (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  ni_E_interrupt ; 
 int ni_alloc_private (struct comedi_device*) ; 
 scalar_t__ ni_boards ; 
 scalar_t__ ni_getboardtype (struct comedi_device*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct comedi_device*) ; 
 int /*<<< orphan*/  win_in (int) ; 
 int /*<<< orphan*/  win_in2 ; 
 int /*<<< orphan*/  win_out2 ; 

__attribute__((used)) static int mio_cs_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct pcmcia_device *link;
	unsigned int irq;
	int ret;

	DPRINTK("mio_cs_attach(dev=%p,it=%p)\n", dev, it);

	link = cur_dev;		/* XXX hack */
	if (!link)
		return -EIO;

	dev->driver = &driver_ni_mio_cs;
	dev->iobase = link->io.BasePort1;

	irq = link->irq.AssignedIRQ;

	printk("comedi%d: %s: DAQCard: io 0x%04lx, irq %u, ",
	       dev->minor, dev->driver->driver_name, dev->iobase, irq);

#if 0
	{
		int i;

		printk(" board fingerprint:");
		for (i = 0; i < 32; i += 2) {
			printk(" %04x %02x", inw(dev->iobase + i),
			       inb(dev->iobase + i + 1));
		}
		printk("\n");
		printk(" board fingerprint (windowed):");
		for (i = 0; i < 10; i++) {
			printk(" 0x%04x", win_in(i));
		}
		printk("\n");
	}
#endif

	dev->board_ptr = ni_boards + ni_getboardtype(dev, link);

	printk(" %s", boardtype.name);
	dev->board_name = boardtype.name;

	ret = request_irq(irq, ni_E_interrupt, NI_E_IRQ_FLAGS,
			  "ni_mio_cs", dev);
	if (ret < 0) {
		printk(" irq not available\n");
		return -EINVAL;
	}
	dev->irq = irq;

	/* allocate private area */
	ret = ni_alloc_private(dev);
	if (ret < 0)
		return ret;

	devpriv->stc_writew = &mio_cs_win_out;
	devpriv->stc_readw = &mio_cs_win_in;
	devpriv->stc_writel = &win_out2;
	devpriv->stc_readl = &win_in2;

	ret = ni_E_init(dev, it);

	if (ret < 0)
		return ret;

	return 0;
}