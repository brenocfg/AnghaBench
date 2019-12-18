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
struct fe_priv {int /*<<< orphan*/  phyaddr; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_READ ; 
 int mii_rw (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nv_link_test(struct net_device *dev)
{
	struct fe_priv *np = netdev_priv(dev);
	int mii_status;

	mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);
	mii_status = mii_rw(dev, np->phyaddr, MII_BMSR, MII_READ);

	/* check phy link status */
	if (!(mii_status & BMSR_LSTATUS))
		return 0;
	else
		return 1;
}