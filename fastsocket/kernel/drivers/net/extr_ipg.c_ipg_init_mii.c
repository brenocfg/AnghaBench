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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct mii_if_info {int (* mdio_read ) (struct net_device*,int,int /*<<< orphan*/ ) ;int phy_id_mask; int reg_num_mask; int phy_id; int /*<<< orphan*/  (* mdio_write ) (struct net_device*,int,int /*<<< orphan*/ ,int) ;struct net_device* dev; } ;
struct ipg_nic_private {int /*<<< orphan*/  pdev; struct mii_if_info mii_if; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int BMCR_ANRESTART ; 
 int BMCR_RESET ; 
 int GMII_PHY_1000BASETCONTROL_PreferMaster ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  PCI_REVISION_ID ; 
 int ipg_find_phyaddr (struct net_device*) ; 
 int /*<<< orphan*/  ipg_set_phy_default_param (int /*<<< orphan*/ ,struct net_device*,int) ; 
 int mdio_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 struct ipg_nic_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipg_init_mii(struct net_device *dev)
{
	struct ipg_nic_private *sp = netdev_priv(dev);
	struct mii_if_info *mii_if = &sp->mii_if;
	int phyaddr;

	mii_if->dev          = dev;
	mii_if->mdio_read    = mdio_read;
	mii_if->mdio_write   = mdio_write;
	mii_if->phy_id_mask  = 0x1f;
	mii_if->reg_num_mask = 0x1f;

	mii_if->phy_id = phyaddr = ipg_find_phyaddr(dev);

	if (phyaddr != 0x1f) {
		u16 mii_phyctrl, mii_1000cr;
		u8 revisionid = 0;

		mii_1000cr  = mdio_read(dev, phyaddr, MII_CTRL1000);
		mii_1000cr |= ADVERTISE_1000FULL | ADVERTISE_1000HALF |
			GMII_PHY_1000BASETCONTROL_PreferMaster;
		mdio_write(dev, phyaddr, MII_CTRL1000, mii_1000cr);

		mii_phyctrl = mdio_read(dev, phyaddr, MII_BMCR);

		/* Set default phyparam */
		pci_read_config_byte(sp->pdev, PCI_REVISION_ID, &revisionid);
		ipg_set_phy_default_param(revisionid, dev, phyaddr);

		/* Reset PHY */
		mii_phyctrl |= BMCR_RESET | BMCR_ANRESTART;
		mdio_write(dev, phyaddr, MII_BMCR, mii_phyctrl);

	}
}