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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {scalar_t__ attached; struct comedi_subdevice* subdevices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int NI_660X_GPCT_SUBDEV (unsigned int) ; 
 int /*<<< orphan*/  ni_660x_handle_gpct_interrupt (struct comedi_device*,struct comedi_subdevice*) ; 
 unsigned int ni_660x_num_counters (struct comedi_device*) ; 
 TYPE_1__* private (struct comedi_device*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ni_660x_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	struct comedi_subdevice *s;
	unsigned i;
	unsigned long flags;

	if (dev->attached == 0)
		return IRQ_NONE;
	/* lock to avoid race with comedi_poll */
	spin_lock_irqsave(&private(dev)->interrupt_lock, flags);
	smp_mb();
	for (i = 0; i < ni_660x_num_counters(dev); ++i) {
		s = dev->subdevices + NI_660X_GPCT_SUBDEV(i);
		ni_660x_handle_gpct_interrupt(dev, s);
	}
	spin_unlock_irqrestore(&private(dev)->interrupt_lock, flags);
	return IRQ_HANDLED;
}