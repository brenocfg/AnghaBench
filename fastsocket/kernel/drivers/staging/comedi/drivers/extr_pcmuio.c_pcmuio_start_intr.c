#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_10__ {TYPE_3__* asics; } ;
struct TYPE_7__ {scalar_t__ stop_count; int active; int asic; unsigned int enabled_mask; int num_asic_chans; int asic_chan; int first_chan; int /*<<< orphan*/  continuous; } ;
struct TYPE_9__ {TYPE_2__ intr; } ;
struct TYPE_8__ {scalar_t__ iobase; } ;
struct TYPE_6__ {struct comedi_cmd cmd; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int CHANS_PER_PORT ; 
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ CR_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ENAB ; 
 int /*<<< orphan*/  PAGE_POL ; 
 scalar_t__ REG_ENAB0 ; 
 TYPE_5__* devpriv ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 TYPE_4__* subpriv ; 
 int /*<<< orphan*/  switch_page (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcmuio_start_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	if (!subpriv->intr.continuous && subpriv->intr.stop_count == 0) {
		/* An empty acquisition! */
		s->async->events |= COMEDI_CB_EOA;
		subpriv->intr.active = 0;
		return 1;
	} else {
		unsigned bits = 0, pol_bits = 0, n;
		int nports, firstport, asic, port;
		struct comedi_cmd *cmd = &s->async->cmd;

		asic = subpriv->intr.asic;
		if (asic < 0)
			return 1;	/* not an interrupt
					   subdev */
		subpriv->intr.enabled_mask = 0;
		subpriv->intr.active = 1;
		nports = subpriv->intr.num_asic_chans / CHANS_PER_PORT;
		firstport = subpriv->intr.asic_chan / CHANS_PER_PORT;
		if (cmd->chanlist) {
			for (n = 0; n < cmd->chanlist_len; n++) {
				bits |= (1U << CR_CHAN(cmd->chanlist[n]));
				pol_bits |= (CR_AREF(cmd->chanlist[n])
					     || CR_RANGE(cmd->
							 chanlist[n]) ? 1U : 0U)
				    << CR_CHAN(cmd->chanlist[n]);
			}
		}
		bits &= ((0x1 << subpriv->intr.num_asic_chans) -
			 1) << subpriv->intr.first_chan;
		subpriv->intr.enabled_mask = bits;

		switch_page(dev, asic, PAGE_ENAB);
		for (port = firstport; port < firstport + nports; ++port) {
			unsigned enab =
			    bits >> (subpriv->intr.first_chan + (port -
								 firstport) *
				     8) & 0xff, pol =
			    pol_bits >> (subpriv->intr.first_chan +
					 (port - firstport) * 8) & 0xff;
			/* set enab intrs for this subdev.. */
			outb(enab,
			     devpriv->asics[asic].iobase + REG_ENAB0 + port);
			switch_page(dev, asic, PAGE_POL);
			outb(pol,
			     devpriv->asics[asic].iobase + REG_ENAB0 + port);
		}
	}
	return 0;
}