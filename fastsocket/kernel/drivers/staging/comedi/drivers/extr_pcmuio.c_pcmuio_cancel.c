#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  spinlock; scalar_t__ active; } ;
struct TYPE_4__ {TYPE_1__ intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmuio_stop_intr (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__* subpriv ; 

__attribute__((used)) static int pcmuio_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	unsigned long flags;

	spin_lock_irqsave(&subpriv->intr.spinlock, flags);
	if (subpriv->intr.active)
		pcmuio_stop_intr(dev, s);
	spin_unlock_irqrestore(&subpriv->intr.spinlock, flags);

	return 0;
}