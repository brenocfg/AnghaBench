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
struct comedi_subdevice {int n_chan; int subdev_flags; int maxdata; scalar_t__ state; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; char* board_name; struct comedi_subdevice* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 scalar_t__ DT2817_CR ; 
 int /*<<< orphan*/  DT2817_SIZE ; 
 int EIO ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 int alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  dt2817_dio_insn_bits ; 
 int /*<<< orphan*/  dt2817_dio_insn_config ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dt2817_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	int ret;
	struct comedi_subdevice *s;
	unsigned long iobase;

	iobase = it->options[0];
	printk("comedi%d: dt2817: 0x%04lx ", dev->minor, iobase);
	if (!request_region(iobase, DT2817_SIZE, "dt2817")) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;
	dev->board_name = "dt2817";

	ret = alloc_subdevices(dev, 1);
	if (ret < 0)
		return ret;

	s = dev->subdevices + 0;

	s->n_chan = 32;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->range_table = &range_digital;
	s->maxdata = 1;
	s->insn_bits = dt2817_dio_insn_bits;
	s->insn_config = dt2817_dio_insn_config;

	s->state = 0;
	outb(0, dev->iobase + DT2817_CR);

	printk("\n");

	return 0;
}