#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int flags; int /*<<< orphan*/  dev_addr; } ;
struct dsa_slave_priv {TYPE_1__* parent; } ;
struct TYPE_4__ {struct net_device* master_netdev; } ;
struct TYPE_3__ {TYPE_2__* dst; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_UP ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_unicast_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_unicast_delete (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_set_mac_address(struct net_device *dev, void *a)
{
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct net_device *master = p->parent->dst->master_netdev;
	struct sockaddr *addr = a;
	int err;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (!(dev->flags & IFF_UP))
		goto out;

	if (compare_ether_addr(addr->sa_data, master->dev_addr)) {
		err = dev_unicast_add(master, addr->sa_data);
		if (err < 0)
			return err;
	}

	if (compare_ether_addr(dev->dev_addr, master->dev_addr))
		dev_unicast_delete(master, dev->dev_addr);

out:
	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	return 0;
}