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
struct diosubd_data {int chans; } ;
struct comedi_subdevice {int subdev_flags; int n_chan; int maxdata; int len_chanlist; void* private; int /*<<< orphan*/  insn_bits; scalar_t__ state; int /*<<< orphan*/ * range_table; int /*<<< orphan*/  type; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int io_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_DO ; 
#define  IO_16b 129 
#define  IO_8b 128 
 int SDF_COMMON ; 
 int SDF_GROUND ; 
 int SDF_LSAMPL ; 
 int SDF_WRITABLE ; 
 int /*<<< orphan*/  pci_dio_insn_bits_do_b ; 
 int /*<<< orphan*/  pci_dio_insn_bits_do_w ; 
 int /*<<< orphan*/  range_digital ; 
 TYPE_1__* this_board ; 

__attribute__((used)) static int pci_dio_add_do(struct comedi_device *dev, struct comedi_subdevice *s,
			  const struct diosubd_data *d, int subdev)
{
	s->type = COMEDI_SUBD_DO;
	s->subdev_flags = SDF_WRITABLE | SDF_GROUND | SDF_COMMON;
	if (d->chans > 16)
		s->subdev_flags |= SDF_LSAMPL;
	s->n_chan = d->chans;
	s->maxdata = 1;
	s->len_chanlist = d->chans;
	s->range_table = &range_digital;
	s->state = 0;
	switch (this_board->io_access) {
	case IO_8b:
		s->insn_bits = pci_dio_insn_bits_do_b;
		break;
	case IO_16b:
		s->insn_bits = pci_dio_insn_bits_do_w;
		break;
	}
	s->private = (void *)d;

	return 0;
}