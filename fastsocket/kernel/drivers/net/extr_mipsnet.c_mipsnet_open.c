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
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct mipsnet_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  MIPSNET_INTCTL_TESTBIT ; 
 int /*<<< orphan*/  interruptControl ; 
 int /*<<< orphan*/  mipsnet_interrupt ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regaddr (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int mipsnet_open(struct net_device *dev)
{
	int err;

	err = request_irq(dev->irq, &mipsnet_interrupt,
			  IRQF_SHARED, dev->name, (void *) dev);
	if (err) {
		release_region(dev->base_addr, sizeof(struct mipsnet_regs));
		return err;
	}

	netif_start_queue(dev);

	/* test interrupt handler */
	outl(MIPSNET_INTCTL_TESTBIT, regaddr(dev, interruptControl));

	return 0;
}