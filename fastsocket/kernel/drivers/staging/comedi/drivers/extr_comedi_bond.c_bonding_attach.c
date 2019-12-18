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
struct comedi_subdevice {int subdev_flags; int maxdata; int /*<<< orphan*/  insn_config; int /*<<< orphan*/  insn_bits; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  type; } ;
struct comedi_device {struct comedi_subdevice* subdevices; int /*<<< orphan*/  board_name; int /*<<< orphan*/  minor; } ;
struct comedi_devconfig {int dummy; } ;
struct Private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndevs; int /*<<< orphan*/  nchans; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DIO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LOG_MSG (char*,int /*<<< orphan*/ ,...) ; 
 int SDF_READABLE ; 
 int SDF_WRITABLE ; 
 scalar_t__ alloc_private (struct comedi_device*,int) ; 
 scalar_t__ alloc_subdevices (struct comedi_device*,int) ; 
 int /*<<< orphan*/  bonding_dio_insn_bits ; 
 int /*<<< orphan*/  bonding_dio_insn_config ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  doDevConfig (struct comedi_device*,struct comedi_devconfig*) ; 
 int /*<<< orphan*/  range_digital ; 

__attribute__((used)) static int bonding_attach(struct comedi_device *dev,
			  struct comedi_devconfig *it)
{
	struct comedi_subdevice *s;

	LOG_MSG("comedi%d\n", dev->minor);

	/*
	 * Allocate the private structure area.  alloc_private() is a
	 * convenient macro defined in comedidev.h.
	 */
	if (alloc_private(dev, sizeof(struct Private)) < 0)
		return -ENOMEM;

	/*
	 * Setup our bonding from config params.. sets up our Private struct..
	 */
	if (!doDevConfig(dev, it))
		return -EINVAL;

	/*
	 * Initialize dev->board_name.  Note that we can use the "thisboard"
	 * macro now, since we just initialized it in the last line.
	 */
	dev->board_name = devpriv->name;

	/*
	 * Allocate the subdevice structures.  alloc_subdevice() is a
	 * convenient macro defined in comedidev.h.
	 */
	if (alloc_subdevices(dev, 1) < 0)
		return -ENOMEM;

	s = dev->subdevices + 0;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = devpriv->nchans;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = bonding_dio_insn_bits;
	s->insn_config = bonding_dio_insn_config;

	LOG_MSG("attached with %u DIO channels coming from %u different "
		"subdevices all bonded together.  "
		"John Lennon would be proud!\n",
		devpriv->nchans, devpriv->ndevs);

	return 1;
}