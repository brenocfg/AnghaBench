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
struct mdio_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  prtad; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MDIO_MMD_DTEXS ; 
 int MDIO_MMD_PCS ; 
 int MDIO_MMD_PHYXS ; 
 int MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int MDIO_STAT1_FAULT ; 
 int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  MDIO_STAT2 ; 
 int MDIO_STAT2_RXFAULT ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int mdio45_links_ok(const struct mdio_if_info *mdio, u32 mmd_mask)
{
	int devad, reg;

	if (!mmd_mask) {
		/* Use absence of XGMII faults in lieu of link state */
		reg = mdio->mdio_read(mdio->dev, mdio->prtad,
				      MDIO_MMD_PHYXS, MDIO_STAT2);
		return reg >= 0 && !(reg & MDIO_STAT2_RXFAULT);
	}

	for (devad = 0; mmd_mask; devad++) {
		if (mmd_mask & (1 << devad)) {
			mmd_mask &= ~(1 << devad);

			/* Reset the latched status and fault flags */
			mdio->mdio_read(mdio->dev, mdio->prtad,
					devad, MDIO_STAT1);
			if (devad == MDIO_MMD_PMAPMD || devad == MDIO_MMD_PCS ||
			    devad == MDIO_MMD_PHYXS || devad == MDIO_MMD_DTEXS)
				mdio->mdio_read(mdio->dev, mdio->prtad,
						devad, MDIO_STAT2);

			/* Check the current status and fault flags */
			reg = mdio->mdio_read(mdio->dev, mdio->prtad,
					      devad, MDIO_STAT1);
			if (reg < 0 ||
			    (reg & (MDIO_STAT1_FAULT | MDIO_STAT1_LSTATUS)) !=
			    MDIO_STAT1_LSTATUS)
				return false;
		}
	}

	return true;
}