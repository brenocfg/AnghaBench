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
struct ethtool_wolinfo {int dummy; } ;
struct cp_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_wol (struct cp_private*,struct ethtool_wolinfo*) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cp_get_wol (struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave (&cp->lock, flags);
	netdev_get_wol (cp, wol);
	spin_unlock_irqrestore (&cp->lock, flags);
}