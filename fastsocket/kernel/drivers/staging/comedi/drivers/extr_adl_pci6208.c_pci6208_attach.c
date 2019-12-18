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
struct pci6208_private {int dummy; } ;
struct comedi_subdevice {int maxdata; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  insn_write; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int /*<<< orphan*/ * options; } ;
struct TYPE_4__ {int /*<<< orphan*/  pci_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ao_chans; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  pci6208_ao_rinsn ; 
 int /*<<< orphan*/  pci6208_ao_winsn ; 
 int pci6208_find_device (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci6208_pci_setup (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int pci6208_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int retval;
	unsigned long io_base;

	printk("comedi%d: pci6208: ", dev->minor);

	retval = alloc_private(dev, sizeof(struct pci6208_private));
	if (retval < 0)
		return retval;

	retval = pci6208_find_device(dev, it->options[0], it->options[1]);
	if (retval < 0)
		return retval;

	retval = pci6208_pci_setup(devpriv->pci_dev, &io_base, dev->minor);
	if (retval < 0)
		return retval;

	dev->iobase = io_base;
	dev->board_name = thisboard->name;

/*
 * Allocate the subdevice structures.  alloc_subdevice() is a
 * convenient macro defined in comedidev.h.
 */
	if (alloc_subdevices(dev, 2) < 0)
		return -ENOMEM;

	s = dev->subdevices + 0;
	/* analog output subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;	/* anything else to add here?? */
	s->n_chan = thisboard->ao_chans;
	s->maxdata = 0xffff;	/* 16-bit DAC */
	s->range_table = &range_bipolar10;	/* this needs to be checked. */
	s->insn_write = pci6208_ao_winsn;
	s->insn_read = pci6208_ao_rinsn;

	/* s=dev->subdevices+1; */
	/* digital i/o subdevice */
	/* s->type=COMEDI_SUBD_DIO; */
	/* s->subdev_flags=SDF_READABLE|SDF_WRITABLE; */
	/* s->n_chan=16; */
	/* s->maxdata=1; */
	/* s->range_table=&range_digital; */
	/* s->insn_bits = pci6208_dio_insn_bits; */
	/* s->insn_config = pci6208_dio_insn_config; */

	printk("attached\n");

	return 1;
}