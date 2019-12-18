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
struct niu {int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  niu_enable_rx_mac (struct niu*,int) ; 
 int /*<<< orphan*/  niu_set_primary_mac (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int niu_set_mac_addr(struct net_device *dev, void *p)
{
	struct niu *np = netdev_priv(dev);
	struct sockaddr *addr = p;
	unsigned long flags;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EINVAL;

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	if (!netif_running(dev))
		return 0;

	spin_lock_irqsave(&np->lock, flags);
	niu_enable_rx_mac(np, 0);
	niu_set_primary_mac(np, dev->dev_addr);
	niu_enable_rx_mac(np, 1);
	spin_unlock_irqrestore(&np->lock, flags);

	return 0;
}