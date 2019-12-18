#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pcmuio_subdev_private {int dummy; } ;
struct pcmuio_private {int dummy; } ;
struct comedi_subdevice {int maxdata; int subdev_flags; int n_chan; int len_chanlist; int /*<<< orphan*/  do_cmdtest; int /*<<< orphan*/  do_cmd; int /*<<< orphan*/  cancel; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/  type; int /*<<< orphan*/ * range_table; scalar_t__ private; } ;
struct comedi_device {unsigned long iobase; unsigned int irq; struct comedi_subdevice* read_subdev; struct comedi_subdevice* subdevices; scalar_t__ n_subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_12__ {TYPE_2__* asics; scalar_t__ sprivs; } ;
struct TYPE_11__ {int /*<<< orphan*/  driver_name; } ;
struct TYPE_7__ {int asic; int first_chan; int asic_chan; int num_asic_chans; int /*<<< orphan*/  spinlock; scalar_t__ stop_count; scalar_t__ active; } ;
struct TYPE_10__ {int* iobases; TYPE_1__ intr; } ;
struct TYPE_9__ {int num_asics; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int num; int iobase; unsigned int irq; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int ASIC_IOSIZE ; 
 int CALC_N_SUBDEVS (int) ; 
 int CHANS_PER_ASIC ; 
 int CHANS_PER_PORT ; 
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTR_PORTS_PER_ASIC ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int MAX_ASICS ; 
 int /*<<< orphan*/  MAX_CHANS_PER_SUBDEV ; 
 int PORTS_PER_ASIC ; 
 int PORTS_PER_SUBDEV ; 
 int SDF_CMD_READ ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 TYPE_6__* devpriv ; 
 TYPE_5__ driver ; 
 int /*<<< orphan*/  free_irq (unsigned int,struct comedi_device*) ; 
 int /*<<< orphan*/  init_asics (struct comedi_device*) ; 
 int /*<<< orphan*/  interrupt_pcmuio ; 
 scalar_t__ kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmuio_cancel ; 
 int /*<<< orphan*/  pcmuio_cmd ; 
 int /*<<< orphan*/  pcmuio_cmdtest ; 
 int /*<<< orphan*/  pcmuio_dio_insn_bits ; 
 int /*<<< orphan*/  pcmuio_dio_insn_config ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_digital ; 
 scalar_t__ request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  request_region (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* subpriv ; 
 TYPE_3__* thisboard ; 

__attribute__((used)) static int pcmuio_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int sdev_no, chans_left, n_subdevs, port, asic, thisasic_chanct = 0;
	unsigned long iobase;
	unsigned int irq[MAX_ASICS];

	iobase = it->options[0];
	irq[0] = it->options[1];
	irq[1] = it->options[2];

	printk("comedi%d: %s: io: %lx ", dev->minor, driver.driver_name,
	       iobase);

	dev->iobase = iobase;

	if (!iobase || !request_region(iobase,
				       thisboard->num_asics * ASIC_IOSIZE,
				       driver.driver_name)) {
		printk("I/O port conflict\n");
		return -EIO;
	}

/*
 * Initialize dev->board_name.  Note that we can use the "thisboard"
 * macro now, since we just initialized it in the last line.
 */
	dev->board_name = thisboard->name;

/*
 * Allocate the private structure area.  alloc_private() is a
 * convenient macro defined in comedidev.h.
 */
	if (alloc_private(dev, sizeof(struct pcmuio_private)) < 0) {
		printk("cannot allocate private data structure\n");
		return -ENOMEM;
	}

	for (asic = 0; asic < MAX_ASICS; ++asic) {
		devpriv->asics[asic].num = asic;
		devpriv->asics[asic].iobase = dev->iobase + asic * ASIC_IOSIZE;
		devpriv->asics[asic].irq = 0;	/* this gets actually set at the end of
						   this function when we
						   request_irqs */
		spin_lock_init(&devpriv->asics[asic].spinlock);
	}

	chans_left = CHANS_PER_ASIC * thisboard->num_asics;
	n_subdevs = CALC_N_SUBDEVS(chans_left);
	devpriv->sprivs =
	    kcalloc(n_subdevs, sizeof(struct pcmuio_subdev_private),
		    GFP_KERNEL);
	if (!devpriv->sprivs) {
		printk("cannot allocate subdevice private data structures\n");
		return -ENOMEM;
	}
	/*
	 * Allocate the subdevice structures.  alloc_subdevice() is a
	 * convenient macro defined in comedidev.h.
	 *
	 * Allocate 2 subdevs (32 + 16 DIO lines) or 3 32 DIO subdevs for the
	 * 96-channel version of the board.
	 */
	if (alloc_subdevices(dev, n_subdevs) < 0) {
		printk("cannot allocate subdevice data structures\n");
		return -ENOMEM;
	}

	port = 0;
	asic = 0;
	for (sdev_no = 0; sdev_no < (int)dev->n_subdevices; ++sdev_no) {
		int byte_no;

		s = dev->subdevices + sdev_no;
		s->private = devpriv->sprivs + sdev_no;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
		s->type = COMEDI_SUBD_DIO;
		s->insn_bits = pcmuio_dio_insn_bits;
		s->insn_config = pcmuio_dio_insn_config;
		s->n_chan = min(chans_left, MAX_CHANS_PER_SUBDEV);
		subpriv->intr.asic = -1;
		subpriv->intr.first_chan = -1;
		subpriv->intr.asic_chan = -1;
		subpriv->intr.num_asic_chans = -1;
		subpriv->intr.active = 0;
		s->len_chanlist = 1;

		/* save the ioport address for each 'port' of 8 channels in the
		   subdevice */
		for (byte_no = 0; byte_no < PORTS_PER_SUBDEV; ++byte_no, ++port) {
			if (port >= PORTS_PER_ASIC) {
				port = 0;
				++asic;
				thisasic_chanct = 0;
			}
			subpriv->iobases[byte_no] =
			    devpriv->asics[asic].iobase + port;

			if (thisasic_chanct <
			    CHANS_PER_PORT * INTR_PORTS_PER_ASIC
			    && subpriv->intr.asic < 0) {
				/* this is an interrupt subdevice, so setup the struct */
				subpriv->intr.asic = asic;
				subpriv->intr.active = 0;
				subpriv->intr.stop_count = 0;
				subpriv->intr.first_chan = byte_no * 8;
				subpriv->intr.asic_chan = thisasic_chanct;
				subpriv->intr.num_asic_chans =
				    s->n_chan - subpriv->intr.first_chan;
				dev->read_subdev = s;
				s->subdev_flags |= SDF_CMD_READ;
				s->cancel = pcmuio_cancel;
				s->do_cmd = pcmuio_cmd;
				s->do_cmdtest = pcmuio_cmdtest;
				s->len_chanlist = subpriv->intr.num_asic_chans;
			}
			thisasic_chanct += CHANS_PER_PORT;
		}
		spin_lock_init(&subpriv->intr.spinlock);

		chans_left -= s->n_chan;

		if (!chans_left) {
			asic = 0;	/* reset the asic to our first asic, to do intr subdevs */
			port = 0;
		}

	}

	init_asics(dev);	/* clear out all the registers, basically */

	for (asic = 0; irq[0] && asic < MAX_ASICS; ++asic) {
		if (irq[asic]
		    && request_irq(irq[asic], interrupt_pcmuio,
				   IRQF_SHARED, thisboard->name, dev)) {
			int i;
			/* unroll the allocated irqs.. */
			for (i = asic - 1; i >= 0; --i) {
				free_irq(irq[i], dev);
				devpriv->asics[i].irq = irq[i] = 0;
			}
			irq[asic] = 0;
		}
		devpriv->asics[asic].irq = irq[asic];
	}

	dev->irq = irq[0];	/* grr.. wish comedi dev struct supported multiple
				   irqs.. */

	if (irq[0]) {
		printk("irq: %u ", irq[0]);
		if (irq[1] && thisboard->num_asics == 2)
			printk("second ASIC irq: %u ", irq[1]);
	} else {
		printk("(IRQ mode disabled) ");
	}

	printk("attached\n");

	return 1;
}