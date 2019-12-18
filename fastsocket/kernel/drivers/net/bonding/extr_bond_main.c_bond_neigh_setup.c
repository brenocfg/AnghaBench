#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct slave {TYPE_1__* dev; } ;
struct net_device_ops {int (* ndo_neigh_setup ) (TYPE_1__*,struct neigh_parms*) ;} ;
struct net_device {int dummy; } ;
struct neigh_parms {int dummy; } ;
struct bonding {struct slave* first_slave; } ;
struct TYPE_2__ {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 struct bonding* netdev_priv (struct net_device*) ; 
 int stub1 (TYPE_1__*,struct neigh_parms*) ; 

__attribute__((used)) static int bond_neigh_setup(struct net_device *dev, struct neigh_parms *parms)
{
	struct bonding *bond = netdev_priv(dev);
	struct slave *slave = bond->first_slave;

	if (slave) {
		const struct net_device_ops *slave_ops
			= slave->dev->netdev_ops;
		if (slave_ops->ndo_neigh_setup)
			return slave_ops->ndo_neigh_setup(slave->dev, parms);
	}
	return 0;
}