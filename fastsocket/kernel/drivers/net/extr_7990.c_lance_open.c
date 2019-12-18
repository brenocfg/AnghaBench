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
struct net_device {int dummy; } ;
struct lance_private {int /*<<< orphan*/  devlock; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  lance_interrupt ; 
 int lance_reset (struct net_device*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int lance_open (struct net_device *dev)
{
        struct lance_private *lp = netdev_priv(dev);
	int res;

        /* Install the Interrupt handler. Or we could shunt this out to specific drivers? */
        if (request_irq(lp->irq, lance_interrupt, IRQF_SHARED, lp->name, dev))
                return -EAGAIN;

        res = lance_reset(dev);
	spin_lock_init(&lp->devlock);
	netif_start_queue (dev);

	return res;
}