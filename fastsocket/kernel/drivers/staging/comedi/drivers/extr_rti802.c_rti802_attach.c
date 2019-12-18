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
struct rti802_private {int dummy; } ;
struct comedi_subdevice {int maxdata; int n_chan; int /*<<< orphan*/ ** range_table_list; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; } ;
struct comedi_device {unsigned long iobase; char* board_name; struct comedi_subdevice* subdevices; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {unsigned long* options; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** range_type_list; int /*<<< orphan*/ * dac_coding; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RTI802_SIZE ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  dac_2comp ; 
 int /*<<< orphan*/  dac_straight ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  range_bipolar10 ; 
 int /*<<< orphan*/  range_unipolar10 ; 
 int /*<<< orphan*/  request_region (unsigned long,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rti802_ao_insn_read ; 
 int /*<<< orphan*/  rti802_ao_insn_write ; 

__attribute__((used)) static int rti802_attach(struct comedi_device *dev, struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int i;
	unsigned long iobase;

	iobase = it->options[0];
	printk("comedi%d: rti802: 0x%04lx ", dev->minor, iobase);
	if (!request_region(iobase, RTI802_SIZE, "rti802")) {
		printk("I/O port conflict\n");
		return -EIO;
	}
	dev->iobase = iobase;

	dev->board_name = "rti802";

	if (alloc_subdevices(dev, 1) < 0
	    || alloc_private(dev, sizeof(struct rti802_private))) {
		return -ENOMEM;
	}

	s = dev->subdevices;
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->maxdata = 0xfff;
	s->n_chan = 8;
	s->insn_read = rti802_ao_insn_read;
	s->insn_write = rti802_ao_insn_write;
	s->range_table_list = devpriv->range_type_list;

	for (i = 0; i < 8; i++) {
		devpriv->dac_coding[i] = (it->options[3 + 2 * i])
		    ? (dac_straight)
		    : (dac_2comp);
		devpriv->range_type_list[i] = (it->options[2 + 2 * i])
		    ? &range_unipolar10 : &range_bipolar10;
	}

	printk("\n");

	return 0;
}