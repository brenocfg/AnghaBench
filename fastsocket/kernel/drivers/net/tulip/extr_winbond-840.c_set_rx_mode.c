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
typedef  int u32 ;
struct netdev_private {int csr6; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __set_rx_mode (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_csr6 (struct net_device*,int) ; 

__attribute__((used)) static void set_rx_mode(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	u32 rx_mode = __set_rx_mode(dev);
	spin_lock_irq(&np->lock);
	update_csr6(dev, (np->csr6 & ~0x00F8) | rx_mode);
	spin_unlock_irq(&np->lock);
}