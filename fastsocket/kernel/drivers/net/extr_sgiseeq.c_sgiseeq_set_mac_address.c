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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct sgiseeq_private {int /*<<< orphan*/  tx_lock; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sgiseeq_set_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sgiseeq_set_mac_address(struct net_device *dev, void *addr)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct sockaddr *sa = addr;

	memcpy(dev->dev_addr, sa->sa_data, dev->addr_len);

	spin_lock_irq(&sp->tx_lock);
	__sgiseeq_set_mac_address(dev);
	spin_unlock_irq(&sp->tx_lock);

	return 0;
}