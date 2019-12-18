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
struct dio200_subdev_intr {int active; int continuous; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  stopcount; } ;
struct comedi_subdevice {TYPE_1__* async; struct dio200_subdev_intr* private; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int stop_src; int start_src; int /*<<< orphan*/  stop_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
#define  TRIG_COUNT 129 
#define  TRIG_INT 128 
 int /*<<< orphan*/  comedi_event (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dio200_inttrig_start_intr ; 
 int dio200_start_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dio200_subdev_intr_cmd(struct comedi_device *dev,
				  struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	struct dio200_subdev_intr *subpriv = s->private;
	unsigned long flags;
	int event = 0;

	spin_lock_irqsave(&subpriv->spinlock, flags);
	subpriv->active = 1;

	/* Set up end of acquisition. */
	switch (cmd->stop_src) {
	case TRIG_COUNT:
		subpriv->continuous = 0;
		subpriv->stopcount = cmd->stop_arg;
		break;
	default:
		/* TRIG_NONE */
		subpriv->continuous = 1;
		subpriv->stopcount = 0;
		break;
	}

	/* Set up start of acquisition. */
	switch (cmd->start_src) {
	case TRIG_INT:
		s->async->inttrig = dio200_inttrig_start_intr;
		break;
	default:
		/* TRIG_NOW */
		event = dio200_start_intr(dev, s);
		break;
	}
	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	if (event) {
		comedi_event(dev, s);
	}

	return 0;
}