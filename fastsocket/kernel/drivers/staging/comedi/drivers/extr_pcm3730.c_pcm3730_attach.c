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
struct comedi_subdevice {int maxdata; int n_chan; void* private; int /*<<< orphan*/ * range_table; void* insn_bits; void* subdev_flags; void* type; } ;
struct comedi_device {unsigned long iobase; char* board_name; struct comedi_subdevice* subdevices; scalar_t__ irq; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 void* COMEDI_SUBD_DI ; 
 void* COMEDI_SUBD_DO ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ PCM3730_DIA ; 
 scalar_t__ PCM3730_DIB ; 
 scalar_t__ PCM3730_DIC ; 
 scalar_t__ PCM3730_DOA ; 
 scalar_t__ PCM3730_DOB ; 
 scalar_t__ PCM3730_DOC ; 
 int /*<<< orphan*/  PCM3730_SIZE ; 
 void* SDF_READABLE ; 
 void* SDF_WRITABLE ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 void* pcm3730_di_insn_bits ; 
 void* pcm3730_do_insn_bits ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_digital ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pcm3730_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase;

	iobase = it->options[0];
	printk("comedi%d: pcm3730: 0x%04lx ", dev->minor, iobase);
	if (!request_region(iobase, PCM3730_SIZE, "pcm3730")) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;
	dev->board_name = "pcm3730";
	dev->iobase = dev->iobase;
	dev->irq = 0;

	if (alloc_subdevices(dev, 6) < 0)
		return -ENOMEM;

	s = dev->subdevices + 0;
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_do_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DOA;

	s = dev->subdevices + 1;
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_do_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DOB;

	s = dev->subdevices + 2;
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_do_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DOC;

	s = dev->subdevices + 3;
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_di_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DIA;

	s = dev->subdevices + 4;
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_di_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DIB;

	s = dev->subdevices + 5;
	s->type = COMEDI_SUBD_DI;
	s->subdev_flags = SDF_READABLE;
	s->maxdata = 1;
	s->n_chan = 8;
	s->insn_bits = pcm3730_di_insn_bits;
	s->range_table = &range_digital;
	s->private = (void *)PCM3730_DIC;

	printk("\n");

	return 0;
}