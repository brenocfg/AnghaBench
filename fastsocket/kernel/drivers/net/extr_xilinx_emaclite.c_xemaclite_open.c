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
struct net_local {TYPE_1__* ndev; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  xemaclite_disable_interrupts (struct net_local*) ; 
 int /*<<< orphan*/  xemaclite_enable_interrupts (struct net_local*) ; 
 int /*<<< orphan*/  xemaclite_interrupt ; 
 int /*<<< orphan*/  xemaclite_set_mac_address (struct net_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xemaclite_open(struct net_device *dev)
{
	struct net_local *lp = (struct net_local *) netdev_priv(dev);
	int retval;

	/* Just to be safe, stop the device first */
	xemaclite_disable_interrupts(lp);

	/* Set the MAC address each time opened */
	xemaclite_set_mac_address(lp, dev->dev_addr);

	/* Grab the IRQ */
	retval = request_irq(dev->irq, &xemaclite_interrupt, 0, dev->name, dev);
	if (retval) {
		dev_err(&lp->ndev->dev, "Could not allocate interrupt %d\n",
			dev->irq);
		return retval;
	}

	/* Enable Interrupts */
	xemaclite_enable_interrupts(lp);

	/* We're ready to go */
	netif_start_queue(dev);

	return 0;
}