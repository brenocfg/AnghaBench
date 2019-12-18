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
struct comedi_subdevice {int subdev_flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * insn_read; int /*<<< orphan*/ * insn_write; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  maxdata; int /*<<< orphan*/  n_chan; } ;
struct comedi_device {struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {scalar_t__* options; } ;
struct board_private_struct {int dummy; } ;
struct TYPE_4__ {int attached_to_8255; int attached_successfully; int /*<<< orphan*/  dio_registers; } ;
struct TYPE_3__ {int dio_method; scalar_t__ dio_chans; int /*<<< orphan*/  ao_bits; int /*<<< orphan*/  ao_chans; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  COMEDI_SUBD_UNUSED ; 
#define  DIO_8255 129 
#define  DIO_INTERNAL 128 
 int ENOMEM ; 
 int ENXIO ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ao_rinsn ; 
 int /*<<< orphan*/  ao_winsn ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  figure_out_maxdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int probe (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_bipolar5 ; 
 int /*<<< orphan*/  subdev_8255_init (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int err;

/*
 * Allocate the private structure area.  alloc_private() is a
 * convenient macro defined in comedidev.h.
 * if this function fails (returns negative) then the private area is
 * kfree'd by comedi
 */
	if (alloc_private(dev, sizeof(struct board_private_struct)) < 0)
		return -ENOMEM;

/*
 * If you can probe the device to determine what device in a series
 * it is, this is the place to do it.  Otherwise, dev->board_ptr
 * should already be initialized.
 */
	err = probe(dev, it);
	if (err)
		return err;

/* Output some info */
	printk("comedi%d: %s: ", dev->minor, thisboard->name);

/*
 * Initialize dev->board_name.  Note that we can use the "thisboard"
 * macro now, since we just initialized it in the last line.
 */
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
	s->subdev_flags = SDF_WRITABLE | SDF_READABLE;
	s->n_chan = thisboard->ao_chans;
	s->maxdata = figure_out_maxdata(thisboard->ao_bits);
	/* this is hard-coded here */
	if (it->options[2]) {
		s->range_table = &range_bipolar10;
	} else {
		s->range_table = &range_bipolar5;
	}
	s->insn_write = &ao_winsn;
	s->insn_read = &ao_rinsn;

	s = dev->subdevices + 1;
	/* digital i/o subdevice */
	if (thisboard->dio_chans) {
		switch (thisboard->dio_method) {
		case DIO_8255:
			/* this is a straight 8255, so register us with the 8255 driver */
			subdev_8255_init(dev, s, NULL, devpriv->dio_registers);
			devpriv->attached_to_8255 = 1;
			break;
		case DIO_INTERNAL:
		default:
			printk("DIO_INTERNAL not implemented yet!\n");
			return -ENXIO;
			break;
		}
	} else {
		s->type = COMEDI_SUBD_UNUSED;
	}

	devpriv->attached_successfully = 1;

	printk("attached\n");

	return 1;
}