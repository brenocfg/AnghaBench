#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct phantom_device {unsigned long status; scalar_t__ caddr; scalar_t__ iaddr; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 unsigned long PHB_RUNNING ; 
 scalar_t__ PHN_CONTROL ; 
 int PHN_CTL_IRQ ; 
 scalar_t__ PHN_IRQCTL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int phantom_status(struct phantom_device *dev, unsigned long newstat)
{
	pr_debug("phantom_status %lx %lx\n", dev->status, newstat);

	if (!(dev->status & PHB_RUNNING) && (newstat & PHB_RUNNING)) {
		atomic_set(&dev->counter, 0);
		iowrite32(PHN_CTL_IRQ, dev->iaddr + PHN_CONTROL);
		iowrite32(0x43, dev->caddr + PHN_IRQCTL);
		ioread32(dev->caddr + PHN_IRQCTL); /* PCI posting */
	} else if ((dev->status & PHB_RUNNING) && !(newstat & PHB_RUNNING)) {
		iowrite32(0, dev->caddr + PHN_IRQCTL);
		ioread32(dev->caddr + PHN_IRQCTL); /* PCI posting */
	}

	dev->status = newstat;

	return 0;
}