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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct fe_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  nv_copy_mac_to_hw (struct net_device*) ; 
 int /*<<< orphan*/  nv_start_rx (struct net_device*) ; 
 int /*<<< orphan*/  nv_stop_rx (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nv_set_mac_address(struct net_device *dev, void *addr)
{
	struct fe_priv *np = netdev_priv(dev);
	struct sockaddr *macaddr = (struct sockaddr*)addr;

	if (!is_valid_ether_addr(macaddr->sa_data))
		return -EADDRNOTAVAIL;

	/* synchronized against open : rtnl_lock() held by caller */
	memcpy(dev->dev_addr, macaddr->sa_data, ETH_ALEN);

	if (netif_running(dev)) {
		netif_tx_lock_bh(dev);
		netif_addr_lock(dev);
		spin_lock_irq(&np->lock);

		/* stop rx engine */
		nv_stop_rx(dev);

		/* set mac address */
		nv_copy_mac_to_hw(dev);

		/* restart rx engine */
		nv_start_rx(dev);
		spin_unlock_irq(&np->lock);
		netif_addr_unlock(dev);
		netif_tx_unlock_bh(dev);
	} else {
		nv_copy_mac_to_hw(dev);
	}
	return 0;
}