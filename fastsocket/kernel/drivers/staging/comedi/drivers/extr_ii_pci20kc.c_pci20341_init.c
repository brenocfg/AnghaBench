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
struct TYPE_2__ {int timebase; int settling_time; } ;
union pci20xxx_subdev_private {scalar_t__ iobase; TYPE_1__ pci20341; } ;
struct comedi_subdevice {int maxdata; int /*<<< orphan*/  range_table; int /*<<< orphan*/  insn_read; int /*<<< orphan*/  len_chanlist; int /*<<< orphan*/  n_chan; int /*<<< orphan*/  subdev_flags; int /*<<< orphan*/  type; union pci20xxx_subdev_private* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_SUBD_AI ; 
 int /*<<< orphan*/  PCI20341_CHAN_NR ; 
 scalar_t__ PCI20341_CONFIG_REG ; 
 int PCI20341_INIT ; 
 scalar_t__ PCI20341_MOD_STATUS ; 
 scalar_t__ PCI20341_OPT_REG ; 
 int PCI20341_PACER ; 
 int PCI20341_REPMODE ; 
 int /*<<< orphan*/  PCI20341_SCANLIST ; 
 scalar_t__ PCI20341_SET_TIME_REG ; 
 int /*<<< orphan*/  SDF_READABLE ; 
 int /*<<< orphan*/  pci20341_insn_read ; 
 int /*<<< orphan*/ * pci20341_ranges ; 
 int* pci20341_settling_time ; 
 int* pci20341_timebase ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pci20341_init(struct comedi_device *dev, struct comedi_subdevice *s,
			 int opt0, int opt1)
{
	union pci20xxx_subdev_private *sdp = s->private;
	int option;

	/* options handling */
	if (opt0 < 0 || opt0 > 3)
		opt0 = 0;
	sdp->pci20341.timebase = pci20341_timebase[opt0];
	sdp->pci20341.settling_time = pci20341_settling_time[opt0];

	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE;
	s->n_chan = PCI20341_CHAN_NR;
	s->len_chanlist = PCI20341_SCANLIST;
	s->insn_read = pci20341_insn_read;
	s->maxdata = 0xffff;
	s->range_table = pci20341_ranges[opt0];

	option = sdp->pci20341.timebase | PCI20341_REPMODE;	/* depends on gain, trigger, repetition mode */

	writeb(PCI20341_INIT, sdp->iobase + PCI20341_CONFIG_REG);	/* initialize Module */
	writeb(PCI20341_PACER, sdp->iobase + PCI20341_MOD_STATUS);	/* set Pacer */
	writeb(option, sdp->iobase + PCI20341_OPT_REG);	/* option register */
	writeb(sdp->pci20341.settling_time, sdp->iobase + PCI20341_SET_TIME_REG);	/* settling time counter */
	/* trigger not implemented */
	return 0;
}