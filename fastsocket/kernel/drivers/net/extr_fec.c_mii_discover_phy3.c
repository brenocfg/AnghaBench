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
typedef  int uint ;
struct net_device {int dummy; } ;
struct fec_enet_private {int phy_id; int phy_id_done; TYPE_1__* phy; int /*<<< orphan*/  phy_addr; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 TYPE_1__** phy_info ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
mii_discover_phy3(uint mii_reg, struct net_device *dev)
{
	struct fec_enet_private *fep;
	int i;

	fep = netdev_priv(dev);
	fep->phy_id |= (mii_reg & 0xffff);
	printk("fec: PHY @ 0x%x, ID 0x%08x", fep->phy_addr, fep->phy_id);

	for(i = 0; phy_info[i]; i++) {
		if(phy_info[i]->id == (fep->phy_id >> 4))
			break;
	}

	if (phy_info[i])
		printk(" -- %s\n", phy_info[i]->name);
	else
		printk(" -- unknown PHY!\n");

	fep->phy = phy_info[i];
	fep->phy_id_done = 1;
}