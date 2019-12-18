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
struct temac_local {int /*<<< orphan*/  dev; int /*<<< orphan*/  indirect_mutex; } ;
struct mii_bus {struct temac_local* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTE_LSW0_OFFSET ; 
 int /*<<< orphan*/  XTE_MIIMAI_OFFSET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int temac_indirect_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_iow (struct temac_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int temac_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	struct temac_local *lp = bus->priv;
	u32 rc;

	/* Write the PHY address to the MIIM Access Initiator register.
	 * When the transfer completes, the PHY register value will appear
	 * in the LSW0 register */
	mutex_lock(&lp->indirect_mutex);
	temac_iow(lp, XTE_LSW0_OFFSET, (phy_id << 5) | reg);
	rc = temac_indirect_in32(lp, XTE_MIIMAI_OFFSET);
	mutex_unlock(&lp->indirect_mutex);

	dev_dbg(lp->dev, "temac_mdio_read(phy_id=%i, reg=%x) == %x\n",
		phy_id, reg, rc);

	return rc;
}