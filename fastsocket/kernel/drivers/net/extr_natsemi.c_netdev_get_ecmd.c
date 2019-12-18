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
typedef  scalar_t__ u32 ;
struct netdev_private {int advertising; int /*<<< orphan*/  phy_addr_external; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct net_device {int if_port; } ;
struct ethtool_cmd {int port; int supported; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  advertising; int /*<<< orphan*/  autoneg; void* transceiver; int /*<<< orphan*/  phy_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_100baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_100baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Full ; 
 int /*<<< orphan*/  ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_FIBRE ; 
 int /*<<< orphan*/  ADVERTISED_MII ; 
 int /*<<< orphan*/  ADVERTISED_TP ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ LPA_100FULL ; 
 scalar_t__ LPA_100HALF ; 
 scalar_t__ LPA_10FULL ; 
 int /*<<< orphan*/  MII_LPA ; 
#define  PORT_FIBRE 130 
#define  PORT_MII 129 
#define  PORT_TP 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 void* XCVR_EXTERNAL ; 
 void* XCVR_INTERNAL ; 
 int mdio_read (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ mii_nway_result (int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_get_ecmd(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct netdev_private *np = netdev_priv(dev);
	u32 tmp;

	ecmd->port        = dev->if_port;
	ecmd->speed       = np->speed;
	ecmd->duplex      = np->duplex;
	ecmd->autoneg     = np->autoneg;
	ecmd->advertising = 0;
	if (np->advertising & ADVERTISE_10HALF)
		ecmd->advertising |= ADVERTISED_10baseT_Half;
	if (np->advertising & ADVERTISE_10FULL)
		ecmd->advertising |= ADVERTISED_10baseT_Full;
	if (np->advertising & ADVERTISE_100HALF)
		ecmd->advertising |= ADVERTISED_100baseT_Half;
	if (np->advertising & ADVERTISE_100FULL)
		ecmd->advertising |= ADVERTISED_100baseT_Full;
	ecmd->supported   = (SUPPORTED_Autoneg |
		SUPPORTED_10baseT_Half  | SUPPORTED_10baseT_Full  |
		SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
		SUPPORTED_TP | SUPPORTED_MII | SUPPORTED_FIBRE);
	ecmd->phy_address = np->phy_addr_external;
	/*
	 * We intentionally report the phy address of the external
	 * phy, even if the internal phy is used. This is necessary
	 * to work around a deficiency of the ethtool interface:
	 * It's only possible to query the settings of the active
	 * port. Therefore
	 * # ethtool -s ethX port mii
	 * actually sends an ioctl to switch to port mii with the
	 * settings that are used for the current active port.
	 * If we would report a different phy address in this
	 * command, then
	 * # ethtool -s ethX port tp;ethtool -s ethX port mii
	 * would unintentionally change the phy address.
	 *
	 * Fortunately the phy address doesn't matter with the
	 * internal phy...
	 */

	/* set information based on active port type */
	switch (ecmd->port) {
	default:
	case PORT_TP:
		ecmd->advertising |= ADVERTISED_TP;
		ecmd->transceiver = XCVR_INTERNAL;
		break;
	case PORT_MII:
		ecmd->advertising |= ADVERTISED_MII;
		ecmd->transceiver = XCVR_EXTERNAL;
		break;
	case PORT_FIBRE:
		ecmd->advertising |= ADVERTISED_FIBRE;
		ecmd->transceiver = XCVR_EXTERNAL;
		break;
	}

	/* if autonegotiation is on, try to return the active speed/duplex */
	if (ecmd->autoneg == AUTONEG_ENABLE) {
		ecmd->advertising |= ADVERTISED_Autoneg;
		tmp = mii_nway_result(
			np->advertising & mdio_read(dev, MII_LPA));
		if (tmp == LPA_100FULL || tmp == LPA_100HALF)
			ecmd->speed  = SPEED_100;
		else
			ecmd->speed  = SPEED_10;
		if (tmp == LPA_100FULL || tmp == LPA_10FULL)
			ecmd->duplex = DUPLEX_FULL;
		else
			ecmd->duplex = DUPLEX_HALF;
	}

	/* ignore maxtxpkt, maxrxpkt for now */

	return 0;
}