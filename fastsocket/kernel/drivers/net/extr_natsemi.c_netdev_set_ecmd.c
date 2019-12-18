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
struct netdev_private {scalar_t__ autoneg; int phy_addr_external; int advertising; scalar_t__ speed; scalar_t__ duplex; scalar_t__ full_duplex; scalar_t__ ignore_phy; } ;
struct net_device {scalar_t__ if_port; } ;
struct ethtool_cmd {scalar_t__ port; scalar_t__ transceiver; scalar_t__ autoneg; int advertising; scalar_t__ speed; scalar_t__ duplex; int phy_address; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_ALL ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ PORT_FIBRE ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ PORT_TP ; 
 int PhyAddrMask ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ XCVR_EXTERNAL ; 
 scalar_t__ XCVR_INTERNAL ; 
 int /*<<< orphan*/  check_link (struct net_device*) ; 
 int /*<<< orphan*/  init_phy_fixup (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  switch_port_external (struct net_device*) ; 
 int /*<<< orphan*/  switch_port_internal (struct net_device*) ; 

__attribute__((used)) static int netdev_set_ecmd(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct netdev_private *np = netdev_priv(dev);

	if (ecmd->port != PORT_TP && ecmd->port != PORT_MII && ecmd->port != PORT_FIBRE)
		return -EINVAL;
	if (ecmd->transceiver != XCVR_INTERNAL && ecmd->transceiver != XCVR_EXTERNAL)
		return -EINVAL;
	if (ecmd->autoneg == AUTONEG_ENABLE) {
		if ((ecmd->advertising & (ADVERTISED_10baseT_Half |
					  ADVERTISED_10baseT_Full |
					  ADVERTISED_100baseT_Half |
					  ADVERTISED_100baseT_Full)) == 0) {
			return -EINVAL;
		}
	} else if (ecmd->autoneg == AUTONEG_DISABLE) {
		if (ecmd->speed != SPEED_10 && ecmd->speed != SPEED_100)
			return -EINVAL;
		if (ecmd->duplex != DUPLEX_HALF && ecmd->duplex != DUPLEX_FULL)
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	/*
	 * If we're ignoring the PHY then autoneg and the internal
	 * transciever are really not going to work so don't let the
	 * user select them.
	 */
	if (np->ignore_phy && (ecmd->autoneg == AUTONEG_ENABLE ||
			       ecmd->port == PORT_TP))
		return -EINVAL;

	/*
	 * maxtxpkt, maxrxpkt: ignored for now.
	 *
	 * transceiver:
	 * PORT_TP is always XCVR_INTERNAL, PORT_MII and PORT_FIBRE are always
	 * XCVR_EXTERNAL. The implementation thus ignores ecmd->transceiver and
	 * selects based on ecmd->port.
	 *
	 * Actually PORT_FIBRE is nearly identical to PORT_MII: it's for fibre
	 * phys that are connected to the mii bus. It's used to apply fibre
	 * specific updates.
	 */

	/* WHEW! now lets bang some bits */

	/* save the parms */
	dev->if_port          = ecmd->port;
	np->autoneg           = ecmd->autoneg;
	np->phy_addr_external = ecmd->phy_address & PhyAddrMask;
	if (np->autoneg == AUTONEG_ENABLE) {
		/* advertise only what has been requested */
		np->advertising &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		if (ecmd->advertising & ADVERTISED_10baseT_Half)
			np->advertising |= ADVERTISE_10HALF;
		if (ecmd->advertising & ADVERTISED_10baseT_Full)
			np->advertising |= ADVERTISE_10FULL;
		if (ecmd->advertising & ADVERTISED_100baseT_Half)
			np->advertising |= ADVERTISE_100HALF;
		if (ecmd->advertising & ADVERTISED_100baseT_Full)
			np->advertising |= ADVERTISE_100FULL;
	} else {
		np->speed  = ecmd->speed;
		np->duplex = ecmd->duplex;
		/* user overriding the initial full duplex parm? */
		if (np->duplex == DUPLEX_HALF)
			np->full_duplex = 0;
	}

	/* get the right phy enabled */
	if (ecmd->port == PORT_TP)
		switch_port_internal(dev);
	else
		switch_port_external(dev);

	/* set parms and see how this affected our link status */
	init_phy_fixup(dev);
	check_link(dev);
	return 0;
}