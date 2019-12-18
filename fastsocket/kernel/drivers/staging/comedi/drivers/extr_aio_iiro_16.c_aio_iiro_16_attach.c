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
struct comedi_subdevice {int n_chan; int maxdata; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  subdev_flags; void* type; } ;
struct comedi_device {int iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int* options; } ;
struct aio_iiro_16_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_IIRO_16_SIZE ; 
 void* COMEDI_SUBD_DIO ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_READABLE ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int /*<<< orphan*/  aio_iiro_16_dio_insn_bits_read ; 
 int /*<<< orphan*/  aio_iiro_16_dio_insn_bits_write ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  request_region (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int aio_iiro_16_attach(struct comedi_device *dev,
			      struct comedi_devconfig *it)
{
	int iobase;
	struct comedi_subdevice *s;

	printk("comedi%d: aio_iiro_16: ", dev->minor);

	dev->board_name = thisboard->name;

	iobase = it->options[0];

	if (!request_region(iobase, AIO_IIRO_16_SIZE, dev->board_name)) {
		printk("I/O port conflict");
		return -EIO;
	}

	dev->iobase = iobase;

	if (alloc_private(dev, sizeof(struct aio_iiro_16_private)) < 0)
		return -ENOMEM;

	if (alloc_subdevices(dev, 2) < 0)
		return -ENOMEM;

	s = dev->subdevices + 0;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = aio_iiro_16_dio_insn_bits_write;

	s = dev->subdevices + 1;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE;
	s->n_chan = 16;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = aio_iiro_16_dio_insn_bits_read;

	printk("attached\n");

	return 1;
}