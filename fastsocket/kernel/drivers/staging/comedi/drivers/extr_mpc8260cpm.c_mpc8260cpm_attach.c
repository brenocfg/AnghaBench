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
struct mpc8260cpm_private {int dummy; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/  insn_config; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; scalar_t__ board; scalar_t__ board_ptr; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int ENOMEM ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 scalar_t__ mpc8260cpm_boards ; 
 int /*<<< orphan*/  mpc8260cpm_dio_bits ; 
 int /*<<< orphan*/  mpc8260cpm_dio_config ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_digital ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static int mpc8260cpm_attach(struct comedi_device *dev,
			     struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;
	int i;

	printk("comedi%d: mpc8260cpm: ", dev->minor);

	dev->board_ptr = mpc8260cpm_boards + dev->board;

	dev->board_name = thisboard->name;

	if (alloc_private(dev, sizeof(struct mpc8260cpm_private)) < 0)
		return -ENOMEM;

	if (alloc_subdevices(dev, 4) < 0)
		return -ENOMEM;

	for (i = 0; i < 4; i++) {
		s = dev->subdevices + i;
		s->type = COMEDI_SUBD_DIO;
		s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
		s->n_chan = 32;
		s->maxdata = 1;
		s->range_table = &range_digital;
		s->insn_config = mpc8260cpm_dio_config;
		s->insn_bits = mpc8260cpm_dio_bits;
	}

	return 1;
}