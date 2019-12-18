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
struct TYPE_2__ {void** ao_range_list; } ;
union pci20xxx_subdev_private {TYPE_1__ pci20006; } ;
struct comedi_subdevice {int n_chan; int len_chanlist; int maxdata; void** range_table_list; int /*<<< orphan*/  insn_write; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; union pci20xxx_subdev_private* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AO ; 
 int /*<<< orphan*/  SDF_WRITABLE ; 
 int /*<<< orphan*/  pci20006_insn_read ; 
 int /*<<< orphan*/  pci20006_insn_write ; 
 void** pci20006_range_list ; 

__attribute__((used)) static int pci20006_init(struct comedi_device *dev, struct comedi_subdevice *s,
			 int opt0, int opt1)
{
	union pci20xxx_subdev_private *sdp = s->private;

	if (opt0 < 0 || opt0 > 2)
		opt0 = 0;
	if (opt1 < 0 || opt1 > 2)
		opt1 = 0;

	sdp->pci20006.ao_range_list[0] = pci20006_range_list[opt0];
	sdp->pci20006.ao_range_list[1] = pci20006_range_list[opt1];

	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 2;
	s->len_chanlist = 2;
	s->insn_read = pci20006_insn_read;
	s->insn_write = pci20006_insn_write;
	s->maxdata = 0xffff;
	s->range_table_list = sdp->pci20006.ao_range_list;
	return 0;
}