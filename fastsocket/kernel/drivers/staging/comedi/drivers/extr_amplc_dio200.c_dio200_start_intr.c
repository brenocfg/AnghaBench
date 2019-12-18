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
struct dio200_subdev_intr {scalar_t__ stopcount; unsigned int valid_isns; unsigned int enabled_isns; int /*<<< orphan*/  iobase; scalar_t__ has_int_sce; scalar_t__ active; int /*<<< orphan*/  continuous; } ;
struct comedi_subdevice {TYPE_1__* async; struct dio200_subdev_intr* private; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_EOA ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dio200_start_intr(struct comedi_device *dev,
			     struct comedi_subdevice *s)
{
	unsigned int n;
	unsigned isn_bits;
	struct dio200_subdev_intr *subpriv = s->private;
	struct comedi_cmd *cmd = &s->async->cmd;
	int retval = 0;

	if (!subpriv->continuous && subpriv->stopcount == 0) {
		/* An empty acquisition! */
		s->async->events |= COMEDI_CB_EOA;
		subpriv->active = 0;
		retval = 1;
	} else {
		/* Determine interrupt sources to enable. */
		isn_bits = 0;
		if (cmd->chanlist) {
			for (n = 0; n < cmd->chanlist_len; n++) {
				isn_bits |= (1U << CR_CHAN(cmd->chanlist[n]));
			}
		}
		isn_bits &= subpriv->valid_isns;
		/* Enable interrupt sources. */
		subpriv->enabled_isns = isn_bits;
		if (subpriv->has_int_sce) {
			outb(isn_bits, subpriv->iobase);
		}
	}

	return retval;
}