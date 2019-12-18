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
struct smc_local {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 unsigned int smc_phy_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_phy_write (struct net_device*,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_phy_reset(struct net_device *dev, int phy)
{
	struct smc_local *lp = netdev_priv(dev);
	unsigned int bmcr;
	int timeout;

	smc_phy_write(dev, phy, MII_BMCR, BMCR_RESET);

	for (timeout = 2; timeout; timeout--) {
		spin_unlock_irq(&lp->lock);
		msleep(50);
		spin_lock_irq(&lp->lock);

		bmcr = smc_phy_read(dev, phy, MII_BMCR);
		if (!(bmcr & BMCR_RESET))
			break;
	}

	return bmcr & BMCR_RESET;
}