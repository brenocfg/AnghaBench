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
struct uml_net_private {int /*<<< orphan*/  lock; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_ether_mac (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uml_net_set_mac(struct net_device *dev, void *addr)
{
	struct uml_net_private *lp = netdev_priv(dev);
	struct sockaddr *hwaddr = addr;

	spin_lock_irq(&lp->lock);
	set_ether_mac(dev, hwaddr->sa_data);
	spin_unlock_irq(&lp->lock);

	return 0;
}