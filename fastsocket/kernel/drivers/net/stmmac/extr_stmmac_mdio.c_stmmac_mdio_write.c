#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct stmmac_priv {TYPE_3__* mac_type; } ;
struct net_device {unsigned long base_addr; } ;
struct mii_bus {struct net_device* priv; } ;
struct TYPE_4__ {unsigned int addr; unsigned int data; } ;
struct TYPE_5__ {TYPE_1__ mii; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int MII_BUSY ; 
 int MII_WRITE ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int readl (unsigned long) ; 
 int /*<<< orphan*/  writel (int,unsigned long) ; 

__attribute__((used)) static int stmmac_mdio_write(struct mii_bus *bus, int phyaddr, int phyreg,
			     u16 phydata)
{
	struct net_device *ndev = bus->priv;
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned long ioaddr = ndev->base_addr;
	unsigned int mii_address = priv->mac_type->hw.mii.addr;
	unsigned int mii_data = priv->mac_type->hw.mii.data;

	u16 value =
	    (((phyaddr << 11) & (0x0000F800)) | ((phyreg << 6) & (0x000007C0)))
	    | MII_WRITE;

	value |= MII_BUSY;

	/* Wait until any existing MII operation is complete */
	do {} while (((readl(ioaddr + mii_address)) & MII_BUSY) == 1);

	/* Set the MII address register to write */
	writel(phydata, ioaddr + mii_data);
	writel(value, ioaddr + mii_address);

	/* Wait until any existing MII operation is complete */
	do {} while (((readl(ioaddr + mii_address)) & MII_BUSY) == 1);

	return 0;
}