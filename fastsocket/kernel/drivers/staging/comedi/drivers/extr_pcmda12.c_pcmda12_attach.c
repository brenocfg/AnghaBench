#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcmda12_private {int dummy; } ;
struct comedi_subdevice {int maxdata; int subdev_flags; int /*<<< orphan*/ * insn_read; int /*<<< orphan*/ * insn_write; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  type; int /*<<< orphan*/ * range_table; int /*<<< orphan*/ * private; } ;
struct comedi_device {unsigned long iobase; struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_6__ {long simultaneous_xfer_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BITS ; 
 int /*<<< orphan*/  CHANS ; 
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IOSIZE ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ao_rinsn ; 
 int /*<<< orphan*/  ao_winsn ; 
 TYPE_3__* devpriv ; 
 TYPE_2__ driver ; 
 int /*<<< orphan*/  pcmda12_ranges ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* thisboard ; 
 int /*<<< orphan*/  zero_chans (struct comedi_device*) ; 

__attribute__((used)) static int pcmda12_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	unsigned long iobase;

	iobase = it->options[0];
	printk("comedi%d: %s: io: %lx %s ", dev->minor, driver.driver_name,
	       iobase, it->options[1] ? "simultaneous xfer mode enabled" : "");

	if (!request_region(iobase, IOSIZE, driver.driver_name)) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;

/*
 * Initialize dev->board_name.  Note that we can use the "thisboard"
 * macro now, since we just initialized it in the last line.
 */
	dev->board_name = thisboard->name;

/*
 * Allocate the private structure area.  alloc_private() is a
 * convenient macro defined in comedidev.h.
 */
	if (alloc_private(dev, sizeof(struct pcmda12_private)) < 0) {
		printk("cannot allocate private data structure\n");
		return -ENOMEM;
	}

	devpriv->simultaneous_xfer_mode = it->options[1];

	/*
	 * Allocate the subdevice structures.  alloc_subdevice() is a
	 * convenient macro defined in comedidev.h.
	 *
	 * Allocate 2 subdevs (32 + 16 DIO lines) or 3 32 DIO subdevs for the
	 * 96-channel version of the board.
	 */
	if (alloc_subdevices(dev, 1) < 0) {
		printk("cannot allocate subdevice data structures\n");
		return -ENOMEM;
	}

	s = dev->subdevices;
	s->private = NULL;
	s->maxdata = (0x1 << BITS) - 1;
	s->range_table = &pcmda12_ranges;
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = CHANS;
	s->insn_write = &ao_winsn;
	s->insn_read = &ao_rinsn;

	zero_chans(dev);	/* clear out all the registers, basically */

	printk("attached\n");

	return 1;
}