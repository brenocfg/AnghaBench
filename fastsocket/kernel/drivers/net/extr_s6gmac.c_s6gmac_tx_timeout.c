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
struct s6gmac {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s6gmac_tx_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s6gmac_tx_timeout(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	unsigned long flags;
	spin_lock_irqsave(&pd->lock, flags);
	s6gmac_tx_interrupt(dev);
	spin_unlock_irqrestore(&pd->lock, flags);
}