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
struct comedi_subdevice {int maxdata; int n_chan; void* private; int /*<<< orphan*/ * range_table; void* insn_bits; void* subdev_flags; void* type; } ;
struct comedi_device {int iobase; struct comedi_subdevice* subdevices; scalar_t__ irq; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int* options; } ;
struct TYPE_2__ {int io_range; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ACL7225_DI_LO ; 
 scalar_t__ ACL7225_RIO_LO ; 
 void* COMEDI_SUBD_DI ; 
 void* COMEDI_SUBD_DO ; 
 int EIO ; 
 int ENOMEM ; 
 void* SDF_READABLE ; 
 void* SDF_WRITABLE ; 
 void* acl7225b_di_insn ; 
 void* acl7225b_do_insn ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  request_region (int,int,char*) ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int acl7225b_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int iobase, iorange;

	iobase = it->options[0];
	iorange = this_board->io_range;
	printk("comedi%d: acl7225b: board=%s 0x%04x ", dev->minor,
	       this_board->name, iobase);
	if (!request_region(iobase, iorange, "acl7225b")) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->board_name = this_board->name;
	dev->iobase = iobase;
	dev->irq = 0;

	if (alloc_subdevices(dev, 3) < 0)
		return -ENOMEM;

	s = dev->subdevices + 0;
	/* Relays outputs */
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = acl7225b_do_insn;
	s->range_table = &range_digital;
	s->private = (void *)ACL7225_RIO_LO;

	s = dev->subdevices + 1;
	/* Relays status */
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = acl7225b_di_insn;
	s->range_table = &range_digital;
	s->private = (void *)ACL7225_RIO_LO;

	s = dev->subdevices + 2;
	/* Isolated digital inputs */
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 16;
	s->insn_bits = acl7225b_di_insn;
	s->range_table = &range_digital;
	s->private = (void *)ACL7225_DI_LO;

	printk("\n");

	return 0;
}