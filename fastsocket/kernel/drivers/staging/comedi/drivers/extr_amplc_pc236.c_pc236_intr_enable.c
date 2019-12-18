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
struct TYPE_2__ {int enable_irq; scalar_t__ lcr_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI236_INTR_ENABLE ; 
 scalar_t__ PLX9052_INTCSR ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pc236_intr_enable(struct comedi_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->enable_irq = 1;
#ifdef CONFIG_COMEDI_PCI
	if (devpriv->lcr_iobase)
		outl(PCI236_INTR_ENABLE, devpriv->lcr_iobase + PLX9052_INTCSR);
#endif
	spin_unlock_irqrestore(&dev->spinlock, flags);
}