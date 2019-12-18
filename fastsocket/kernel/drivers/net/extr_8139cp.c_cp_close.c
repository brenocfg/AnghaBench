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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp_free_rings (struct cp_private*) ; 
 int /*<<< orphan*/  cp_stop_hw (struct cp_private*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct cp_private*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cp_close (struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;

	napi_disable(&cp->napi);

	if (netif_msg_ifdown(cp))
		pr_debug("%s: disabling interface\n", dev->name);

	spin_lock_irqsave(&cp->lock, flags);

	netif_stop_queue(dev);
	netif_carrier_off(dev);

	cp_stop_hw(cp);

	spin_unlock_irqrestore(&cp->lock, flags);

	free_irq(dev->irq, dev);

	cp_free_rings(cp);
	return 0;
}