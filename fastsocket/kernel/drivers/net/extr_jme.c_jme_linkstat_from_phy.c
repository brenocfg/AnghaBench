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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {TYPE_1__ mii_if; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMSR_ANCOMP ; 
 int MII_BMSR ; 
 int PHY_LINK_AUTONEG_COMPLETE ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
jme_linkstat_from_phy(struct jme_adapter *jme)
{
	u32 phylink, bmsr;

	phylink = jme_mdio_read(jme->dev, jme->mii_if.phy_id, 17);
	bmsr = jme_mdio_read(jme->dev, jme->mii_if.phy_id, MII_BMSR);
	if (bmsr & BMSR_ANCOMP)
		phylink |= PHY_LINK_AUTONEG_COMPLETE;

	return phylink;
}