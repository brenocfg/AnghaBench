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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int gpcs_address; } ;
struct emac_instance {struct emac_instance* mdio_instance; TYPE_1__ phy; } ;

/* Variables and functions */
 int __emac_mdio_read (struct emac_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct emac_instance* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int emac_mdio_read(struct net_device *ndev, int id, int reg)
{
	struct emac_instance *dev = netdev_priv(ndev);
	int res;

	res = __emac_mdio_read((dev->mdio_instance &&
				dev->phy.gpcs_address != id) ?
				dev->mdio_instance : dev,
			       (u8) id, (u8) reg);
	return res;
}