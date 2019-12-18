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
struct net_device {int dummy; } ;
struct amd8111e_priv {int ext_phy_option; int /*<<< orphan*/  ext_phy_addr; } ;

/* Variables and functions */
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_ALL ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
#define  SPEED100_FULL 132 
#define  SPEED100_HALF 131 
#define  SPEED10_FULL 130 
#define  SPEED10_HALF 129 
#define  SPEED_AUTONEG 128 
 int amd8111e_mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amd8111e_mdio_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void amd8111e_set_ext_phy(struct net_device *dev)
{
	struct amd8111e_priv *lp = netdev_priv(dev);
	u32 bmcr,advert,tmp;

	/* Determine mii register values to set the speed */
	advert = amd8111e_mdio_read(dev, lp->ext_phy_addr, MII_ADVERTISE);
	tmp = advert & ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
	switch (lp->ext_phy_option){

		default:
		case SPEED_AUTONEG: /* advertise all values */
			tmp |= ( ADVERTISE_10HALF|ADVERTISE_10FULL|
				ADVERTISE_100HALF|ADVERTISE_100FULL) ;
			break;
		case SPEED10_HALF:
			tmp |= ADVERTISE_10HALF;
			break;
		case SPEED10_FULL:
			tmp |= ADVERTISE_10FULL;
			break;
		case SPEED100_HALF:
			tmp |= ADVERTISE_100HALF;
			break;
		case SPEED100_FULL:
			tmp |= ADVERTISE_100FULL;
			break;
	}

	if(advert != tmp)
		amd8111e_mdio_write(dev, lp->ext_phy_addr, MII_ADVERTISE, tmp);
	/* Restart auto negotiation */
	bmcr = amd8111e_mdio_read(dev, lp->ext_phy_addr, MII_BMCR);
	bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	amd8111e_mdio_write(dev, lp->ext_phy_addr, MII_BMCR, bmcr);

}