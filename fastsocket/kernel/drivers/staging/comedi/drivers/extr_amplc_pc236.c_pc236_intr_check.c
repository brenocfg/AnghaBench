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
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {scalar_t__ lcr_iobase; scalar_t__ enable_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI236_INTR_ENABLE ; 
 scalar_t__ PLX9052_INTCSR ; 
 int PLX9052_INTCSR_LI1STAT_INACTIVE ; 
 int PLX9052_INTCSR_LI1STAT_MASK ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pc236_intr_check(struct comedi_device *dev)
{
	int retval = 0;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	if (devpriv->enable_irq) {
		retval = 1;
#ifdef CONFIG_COMEDI_PCI
		if (devpriv->lcr_iobase) {
			if ((inl(devpriv->lcr_iobase + PLX9052_INTCSR)
			     & PLX9052_INTCSR_LI1STAT_MASK)
			    == PLX9052_INTCSR_LI1STAT_INACTIVE) {
				retval = 0;
			} else {
				/* Clear interrupt and keep it enabled. */
				outl(PCI236_INTR_ENABLE,
				     devpriv->lcr_iobase + PLX9052_INTCSR);
			}
		}
#endif
	}
	spin_unlock_irqrestore(&dev->spinlock, flags);

	return retval;
}