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
typedef  int /*<<< orphan*/  u16 ;
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; scalar_t__* data; } ;
struct smsc95xx_priv {int mac_cr; int /*<<< orphan*/  mac_cr_lock; } ;
struct ethtool_cmd {scalar_t__ duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  INT_STS ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_FDPX_ ; 
 int MAC_CR_RCVOWN_ ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  PHY_INT_SRC ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_check_media (struct mii_if_info*,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (struct mii_if_info*,struct ethtool_cmd*) ; 
 scalar_t__ netif_msg_link (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc95xx_phy_update_flowcontrol (struct usbnet*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc95xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int smsc95xx_link_reset(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	struct mii_if_info *mii = &dev->mii;
	struct ethtool_cmd ecmd;
	unsigned long flags;
	u16 lcladv, rmtadv;
	u32 intdata;

	/* clear interrupt status */
	smsc95xx_mdio_read(dev->net, mii->phy_id, PHY_INT_SRC);
	intdata = 0xFFFFFFFF;
	smsc95xx_write_reg(dev, INT_STS, intdata);

	mii_check_media(mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	lcladv = smsc95xx_mdio_read(dev->net, mii->phy_id, MII_ADVERTISE);
	rmtadv = smsc95xx_mdio_read(dev->net, mii->phy_id, MII_LPA);

	if (netif_msg_link(dev))
		devdbg(dev, "speed: %d duplex: %d lcladv: %04x rmtadv: %04x",
			ecmd.speed, ecmd.duplex, lcladv, rmtadv);

	spin_lock_irqsave(&pdata->mac_cr_lock, flags);
	if (ecmd.duplex != DUPLEX_FULL) {
		pdata->mac_cr &= ~MAC_CR_FDPX_;
		pdata->mac_cr |= MAC_CR_RCVOWN_;
	} else {
		pdata->mac_cr &= ~MAC_CR_RCVOWN_;
		pdata->mac_cr |= MAC_CR_FDPX_;
	}
	spin_unlock_irqrestore(&pdata->mac_cr_lock, flags);

	smsc95xx_write_reg(dev, MAC_CR, pdata->mac_cr);

	smsc95xx_phy_update_flowcontrol(dev, ecmd.duplex, lcladv, rmtadv);

	return 0;
}