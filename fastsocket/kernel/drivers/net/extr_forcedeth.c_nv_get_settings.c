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
struct fe_priv {int linkspeed; scalar_t__ gigabit; int /*<<< orphan*/  lock; int /*<<< orphan*/  phyaddr; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct ethtool_cmd {int speed; int duplex; int supported; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  advertising; scalar_t__ autoneg; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_1000baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_MII ; 
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_READ ; 
#define  NVREG_LINKSPEED_10 130 
#define  NVREG_LINKSPEED_100 129 
#define  NVREG_LINKSPEED_1000 128 
 int NVREG_LINKSPEED_MASK ; 
 scalar_t__ PHY_GIGABIT ; 
 int /*<<< orphan*/  PORT_MII ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  XCVR_EXTERNAL ; 
 int mii_rw (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ nv_update_linkspeed (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nv_get_settings(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct fe_priv *np = netdev_priv(dev);
	int adv;

	spin_lock_irq(&np->lock);
	ecmd->port = PORT_MII;
	if (!netif_running(dev)) {
		/* We do not track link speed / duplex setting if the
		 * interface is disabled. Force a link check */
		if (nv_update_linkspeed(dev)) {
			if (!netif_carrier_ok(dev))
				netif_carrier_on(dev);
		} else {
			if (netif_carrier_ok(dev))
				netif_carrier_off(dev);
		}
	}

	if (netif_carrier_ok(dev)) {
		switch(np->linkspeed & (NVREG_LINKSPEED_MASK)) {
		case NVREG_LINKSPEED_10:
			ecmd->speed = SPEED_10;
			break;
		case NVREG_LINKSPEED_100:
			ecmd->speed = SPEED_100;
			break;
		case NVREG_LINKSPEED_1000:
			ecmd->speed = SPEED_1000;
			break;
		}
		ecmd->duplex = DUPLEX_HALF;
		if (np->duplex)
			ecmd->duplex = DUPLEX_FULL;
	} else {
		ecmd->speed = -1;
		ecmd->duplex = -1;
	}

	ecmd->autoneg = np->autoneg;

	ecmd->advertising = ADVERTISED_MII;
	if (np->autoneg) {
		ecmd->advertising |= ADVERTISED_Autoneg;
		adv = mii_rw(dev, np->phyaddr, MII_ADVERTISE, MII_READ);
		if (adv & ADVERTISE_10HALF)
			ecmd->advertising |= ADVERTISED_10baseT_Half;
		if (adv & ADVERTISE_10FULL)
			ecmd->advertising |= ADVERTISED_10baseT_Full;
		if (adv & ADVERTISE_100HALF)
			ecmd->advertising |= ADVERTISED_100baseT_Half;
		if (adv & ADVERTISE_100FULL)
			ecmd->advertising |= ADVERTISED_100baseT_Full;
		if (np->gigabit == PHY_GIGABIT) {
			adv = mii_rw(dev, np->phyaddr, MII_CTRL1000, MII_READ);
			if (adv & ADVERTISE_1000FULL)
				ecmd->advertising |= ADVERTISED_1000baseT_Full;
		}
	}
	ecmd->supported = (SUPPORTED_Autoneg |
		SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
		SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		SUPPORTED_MII);
	if (np->gigabit == PHY_GIGABIT)
		ecmd->supported |= SUPPORTED_1000baseT_Full;

	ecmd->phy_address = np->phyaddr;
	ecmd->transceiver = XCVR_EXTERNAL;

	/* ignore maxtxpkt, maxrxpkt for now */
	spin_unlock_irq(&np->lock);
	return 0;
}