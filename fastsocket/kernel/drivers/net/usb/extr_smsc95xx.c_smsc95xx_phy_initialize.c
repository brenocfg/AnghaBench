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
struct TYPE_2__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  phy_id; int /*<<< orphan*/  (* mdio_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;
struct usbnet {TYPE_1__ mii; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int ADVERTISE_ALL ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHY_INT_MASK ; 
 int PHY_INT_MASK_DEFAULT_ ; 
 int /*<<< orphan*/  PHY_INT_SRC ; 
 int /*<<< orphan*/  SMSC95XX_INTERNAL_PHY_ID ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*) ; 
 int /*<<< orphan*/  mii_nway_restart (TYPE_1__*) ; 
 scalar_t__ netif_msg_ifup (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc95xx_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc95xx_phy_initialize(struct usbnet *dev)
{
	/* Initialize MII structure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_read = smsc95xx_mdio_read;
	dev->mii.mdio_write = smsc95xx_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = SMSC95XX_INTERNAL_PHY_ID;

	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);
	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP |
		ADVERTISE_PAUSE_ASYM);

	/* read to clear */
	smsc95xx_mdio_read(dev->net, dev->mii.phy_id, PHY_INT_SRC);

	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_MASK,
		PHY_INT_MASK_DEFAULT_);
	mii_nway_restart(&dev->mii);

	if (netif_msg_ifup(dev))
		devdbg(dev, "phy initialised succesfully");
	return 0;
}