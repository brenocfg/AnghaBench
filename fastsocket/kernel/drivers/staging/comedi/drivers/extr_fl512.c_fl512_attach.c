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
struct fl512_private {int dummy; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  insn_write; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; char* board_name; struct comedi_subdevice* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FL512_SIZE ; 
 int SDF_GROUND ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  fl512_ai_insn ; 
 int /*<<< orphan*/  fl512_ao_insn ; 
 int /*<<< orphan*/  fl512_ao_insn_readback ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_fl512 ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fl512_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	unsigned long iobase;
	struct comedi_subdevice *s;	/* pointer to the subdevice:
					   Analog in, Analog out, ( not made ->and Digital IO) */

	iobase = it->options[0];
	printk("comedi:%d fl512: 0x%04lx", dev->minor, iobase);
	if (!request_region(iobase, FL512_SIZE, "fl512")) {
		printk(" I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;
	dev->board_name = "fl512";
	if (alloc_private(dev, sizeof(struct fl512_private)) < 0)
		return -ENOMEM;

#if DEBUG
	printk("malloc ok\n");
#endif

	if (alloc_subdevices(dev, 2) < 0)
		return -ENOMEM;

	/*
	 * this if the definitions of the supdevices, 2 have been defined
	 */
	/* Analog indput */
	s = dev->subdevices + 0;
	s->type = COMEDI_SUBD_AI;	/* define subdevice as Analog In   */
	s->subdev_flags = SDF_READABLE | SDF_GROUND;	/* you can read it from userspace  */
	s->n_chan = 16;		/* Number of Analog input channels */
	s->maxdata = 0x0fff;	/* accept only 12 bits of data     */
	s->range_table = &range_fl512;	/* device use one of the ranges    */
	s->insn_read = fl512_ai_insn;	/* function to call when read AD   */
	printk("comedi: fl512: subdevice 0 initialized\n");

	/* Analog output */
	s = dev->subdevices + 1;
	s->type = COMEDI_SUBD_AO;	/* define subdevice as Analog OUT   */
	s->subdev_flags = SDF_WRITABLE;	/* you can write it from userspace  */
	s->n_chan = 2;		/* Number of Analog output channels */
	s->maxdata = 0x0fff;	/* accept only 12 bits of data      */
	s->range_table = &range_fl512;	/* device use one of the ranges     */
	s->insn_write = fl512_ao_insn;	/* function to call when write DA   */
	s->insn_read = fl512_ao_insn_readback;	/* function to call when reading DA   */
	printk("comedi: fl512: subdevice 1 initialized\n");

	return 1;
}