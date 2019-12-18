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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_if_info {int (* mdio_read ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int full_duplex; scalar_t__ supports_gmii; int /*<<< orphan*/  phy_id; struct net_device* dev; } ;
struct ethtool_cmd {int supported; int advertising; int lp_advertising; int duplex; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  transceiver; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int BMSR_ANEGCOMPLETE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int /*<<< orphan*/  MDIO_SUPPORTS_C22 ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  XCVR_INTERNAL ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int /*<<< orphan*/ ) ; 
 int mii_ctrl1000_to_ethtool_adv_t (int) ; 
 int mii_get_an (struct mii_if_info*,int /*<<< orphan*/ ) ; 
 int mii_stat1000_to_ethtool_lpa_t (int) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mii_ethtool_gset(struct mii_if_info *mii, struct ethtool_cmd *ecmd)
{
	struct net_device *dev = mii->dev;
	u16 bmcr, bmsr, ctrl1000 = 0, stat1000 = 0;
	u32 nego;

	ecmd->supported =
	    (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
	     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
	     SUPPORTED_Autoneg | SUPPORTED_TP | SUPPORTED_MII);
	if (mii->supports_gmii)
		ecmd->supported |= SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full;

	/* only supports twisted-pair */
	ecmd->port = PORT_MII;

	/* only supports internal transceiver */
	ecmd->transceiver = XCVR_INTERNAL;

	/* this isn't fully supported at higher layers */
	ecmd->phy_address = mii->phy_id;
	ecmd->mdio_support = MDIO_SUPPORTS_C22;

	ecmd->advertising = ADVERTISED_TP | ADVERTISED_MII;

	bmcr = mii->mdio_read(dev, mii->phy_id, MII_BMCR);
	bmsr = mii->mdio_read(dev, mii->phy_id, MII_BMSR);
	if (mii->supports_gmii) {
 		ctrl1000 = mii->mdio_read(dev, mii->phy_id, MII_CTRL1000);
		stat1000 = mii->mdio_read(dev, mii->phy_id, MII_STAT1000);
	}
	if (bmcr & BMCR_ANENABLE) {
		ecmd->advertising |= ADVERTISED_Autoneg;
		ecmd->autoneg = AUTONEG_ENABLE;

		ecmd->advertising |= mii_get_an(mii, MII_ADVERTISE);
		if (mii->supports_gmii)
			ecmd->advertising |=
					mii_ctrl1000_to_ethtool_adv_t(ctrl1000);

		if (bmsr & BMSR_ANEGCOMPLETE) {
			ecmd->lp_advertising = mii_get_an(mii, MII_LPA);
			ecmd->lp_advertising |=
					mii_stat1000_to_ethtool_lpa_t(stat1000);
		} else {
			ecmd->lp_advertising = 0;
		}

		nego = ecmd->advertising & ecmd->lp_advertising;

		if (nego & (ADVERTISED_1000baseT_Full |
			    ADVERTISED_1000baseT_Half)) {
			ethtool_cmd_speed_set(ecmd, SPEED_1000);
			ecmd->duplex = !!(nego & ADVERTISED_1000baseT_Full);
		} else if (nego & (ADVERTISED_100baseT_Full |
				   ADVERTISED_100baseT_Half)) {
			ethtool_cmd_speed_set(ecmd, SPEED_100);
			ecmd->duplex = !!(nego & ADVERTISED_100baseT_Full);
		} else {
			ethtool_cmd_speed_set(ecmd, SPEED_10);
			ecmd->duplex = !!(nego & ADVERTISED_10baseT_Full);
		}
	} else {
		ecmd->autoneg = AUTONEG_DISABLE;

		ethtool_cmd_speed_set(ecmd,
				      ((bmcr & BMCR_SPEED1000 &&
					(bmcr & BMCR_SPEED100) == 0) ?
				       SPEED_1000 :
				       ((bmcr & BMCR_SPEED100) ?
					SPEED_100 : SPEED_10)));
		ecmd->duplex = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
	}

	mii->full_duplex = ecmd->duplex;

	/* ignore maxtxpkt, maxrxpkt for now */

	return 0;
}