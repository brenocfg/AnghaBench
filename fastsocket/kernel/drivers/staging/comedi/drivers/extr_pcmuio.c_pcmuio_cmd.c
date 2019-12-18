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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int stop_src; int start_src; int /*<<< orphan*/  stop_arg; } ;
struct TYPE_5__ {int active; int continuous; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  stop_count; } ;
struct TYPE_6__ {TYPE_2__ intr; } ;
struct TYPE_4__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
#define  TRIG_COUNT 129 
#define  TRIG_INT 128 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pcmuio_inttrig_start_intr ; 
 int pcmuio_start_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_3__* subpriv ; 

__attribute__((used)) static int pcmuio_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned long flags;
	int event = 0;

	spin_lock_irqsave(&subpriv->intr.spinlock, flags);
	subpriv->intr.active = 1;

	/* Set up end of acquisition. */
	switch (cmd->stop_src) {
	case TRIG_COUNT:
		subpriv->intr.continuous = 0;
		subpriv->intr.stop_count = cmd->stop_arg;
		break;
	default:
		/* TRIG_NONE */
		subpriv->intr.continuous = 1;
		subpriv->intr.stop_count = 0;
		break;
	}

	/* Set up start of acquisition. */
	switch (cmd->start_src) {
	case TRIG_INT:
		s->async->inttrig = pcmuio_inttrig_start_intr;
		break;
	default:
		/* TRIG_NOW */
		event = pcmuio_start_intr(dev, s);
		break;
	}
	spin_unlock_irqrestore(&subpriv->intr.spinlock, flags);

	if (event) {
		comedi_event(dev, s);
	}

	return 0;
}