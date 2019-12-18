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
struct phy_device {TYPE_1__* drv; } ;
struct TYPE_2__ {scalar_t__ phy_id; } ;

/* Variables and functions */
 scalar_t__ BRCM_PHY_MODEL (struct phy_device*) ; 
 int MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA ; 
 int MII_BCM54XX_AUXCTL_ACTL_TX_6DB ; 
 int /*<<< orphan*/  MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL ; 
 int /*<<< orphan*/  MII_BCM54XX_EXP_EXP08 ; 
 int MII_BCM54XX_EXP_EXP08_RJCT_2MHZ ; 
 int /*<<< orphan*/  MII_BCM54XX_EXP_EXP75 ; 
 int MII_BCM54XX_EXP_EXP75_CM_OSC ; 
 scalar_t__ PHY_ID_BCM50610 ; 
 scalar_t__ PHY_ID_BCM50610M ; 
 scalar_t__ PHY_ID_BCM57780 ; 
 int bcm50610_a0_workaround (struct phy_device*) ; 
 int bcm54xx_auxctl_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int bcm54xx_exp_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int bcm54xx_exp_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm54xx_phydsp_config(struct phy_device *phydev)
{
	int err, err2;

	/* Enable the SMDSP clock */
	err = bcm54xx_auxctl_write(phydev,
				   MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL,
				   MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA |
				   MII_BCM54XX_AUXCTL_ACTL_TX_6DB);
	if (err < 0)
		return err;

	if (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	    BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) {
		/* Clear bit 9 to fix a phy interop issue. */
		err = bcm54xx_exp_write(phydev, MII_BCM54XX_EXP_EXP08,
					MII_BCM54XX_EXP_EXP08_RJCT_2MHZ);
		if (err < 0)
			goto error;

		if (phydev->drv->phy_id == PHY_ID_BCM50610) {
			err = bcm50610_a0_workaround(phydev);
			if (err < 0)
				goto error;
		}
	}

	if (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM57780) {
		int val;

		val = bcm54xx_exp_read(phydev, MII_BCM54XX_EXP_EXP75);
		if (val < 0)
			goto error;

		val |= MII_BCM54XX_EXP_EXP75_CM_OSC;
		err = bcm54xx_exp_write(phydev, MII_BCM54XX_EXP_EXP75, val);
	}

error:
	/* Disable the SMDSP clock */
	err2 = bcm54xx_auxctl_write(phydev,
				    MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL,
				    MII_BCM54XX_AUXCTL_ACTL_TX_6DB);

	/* Return the first error reported. */
	return err ? err : err2;
}