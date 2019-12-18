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
struct comedi_subdevice {scalar_t__ type; int n_chan; int maxdata; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  range_table; } ;
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_2__ {unsigned int iosize; int n_chan; scalar_t__ type; int n_bits; int /*<<< orphan*/  insnbits; int /*<<< orphan*/  rinsn; int /*<<< orphan*/  winsn; int /*<<< orphan*/  range; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ COMEDI_SUBD_AO ; 
 scalar_t__ COMEDI_SUBD_DO ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  request_region (unsigned long,unsigned int,char*) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int poc_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase;
	unsigned int iosize;

	iobase = it->options[0];
	printk("comedi%d: poc: using %s iobase 0x%lx\n", dev->minor,
	       this_board->name, iobase);

	dev->board_name = this_board->name;

	if (iobase == 0) {
		printk("io base address required\n");
		return -EINVAL;
	}

	iosize = this_board->iosize;
	/* check if io addresses are available */
	if (!request_region(iobase, iosize, "dac02")) {
		printk
		    ("I/O port conflict: failed to allocate ports 0x%lx to 0x%lx\n",
		     iobase, iobase + iosize - 1);
		return -EIO;
	}
	dev->iobase = iobase;

	if (alloc_subdevices(dev, 1) < 0)
		return -ENOMEM;
	if (alloc_private(dev, sizeof(unsigned int) * this_board->n_chan) < 0)
		return -ENOMEM;

	/* analog output subdevice */
	s = dev->subdevices + 0;
	s->type = this_board->type;
	s->n_chan = this_board->n_chan;
	s->maxdata = (1 << this_board->n_bits) - 1;
	s->range_table = this_board->range;
	s->insn_write = this_board->winsn;
	s->insn_read = this_board->rinsn;
	s->insn_bits = this_board->insnbits;
	if (s->type == COMEDI_SUBD_AO || s->type == COMEDI_SUBD_DO) {
		s->subdev_flags = SDF_WRITABLE;
	}

	return 0;
}