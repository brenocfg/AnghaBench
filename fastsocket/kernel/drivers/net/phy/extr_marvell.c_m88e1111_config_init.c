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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_M1111_HWCFG_FIBER_COPPER_AUTO ; 
 int MII_M1111_HWCFG_FIBER_COPPER_RES ; 
 int MII_M1111_HWCFG_MODE_COPPER_RGMII ; 
 int MII_M1111_HWCFG_MODE_FIBER_RGMII ; 
 int MII_M1111_HWCFG_MODE_MASK ; 
 int MII_M1111_HWCFG_MODE_SGMII_NO_CLK ; 
 int /*<<< orphan*/  MII_M1111_PHY_EXT_CR ; 
 int /*<<< orphan*/  MII_M1111_PHY_EXT_SR ; 
 int MII_M1111_RX_DELAY ; 
 int MII_M1111_TX_DELAY ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int m88e1111_config_init(struct phy_device *phydev)
{
	int err;
	int temp;

	/* Enable Fiber/Copper auto selection */
	temp = phy_read(phydev, MII_M1111_PHY_EXT_SR);
	temp &= ~MII_M1111_HWCFG_FIBER_COPPER_AUTO;
	phy_write(phydev, MII_M1111_PHY_EXT_SR, temp);

	temp = phy_read(phydev, MII_BMCR);
	temp |= BMCR_RESET;
	phy_write(phydev, MII_BMCR, temp);

	if ((phydev->interface == PHY_INTERFACE_MODE_RGMII) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)) {

		temp = phy_read(phydev, MII_M1111_PHY_EXT_CR);
		if (temp < 0)
			return temp;

		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID) {
			temp |= (MII_M1111_RX_DELAY | MII_M1111_TX_DELAY);
		} else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
			temp &= ~MII_M1111_TX_DELAY;
			temp |= MII_M1111_RX_DELAY;
		} else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
			temp &= ~MII_M1111_RX_DELAY;
			temp |= MII_M1111_TX_DELAY;
		}

		err = phy_write(phydev, MII_M1111_PHY_EXT_CR, temp);
		if (err < 0)
			return err;

		temp = phy_read(phydev, MII_M1111_PHY_EXT_SR);
		if (temp < 0)
			return temp;

		temp &= ~(MII_M1111_HWCFG_MODE_MASK);

		if (temp & MII_M1111_HWCFG_FIBER_COPPER_RES)
			temp |= MII_M1111_HWCFG_MODE_FIBER_RGMII;
		else
			temp |= MII_M1111_HWCFG_MODE_COPPER_RGMII;

		err = phy_write(phydev, MII_M1111_PHY_EXT_SR, temp);
		if (err < 0)
			return err;
	}

	if (phydev->interface == PHY_INTERFACE_MODE_SGMII) {
		temp = phy_read(phydev, MII_M1111_PHY_EXT_SR);
		if (temp < 0)
			return temp;

		temp &= ~(MII_M1111_HWCFG_MODE_MASK);
		temp |= MII_M1111_HWCFG_MODE_SGMII_NO_CLK;
		temp |= MII_M1111_HWCFG_FIBER_COPPER_AUTO;

		err = phy_write(phydev, MII_M1111_PHY_EXT_SR, temp);
		if (err < 0)
			return err;
	}

	err = phy_write(phydev, MII_BMCR, BMCR_RESET);
	if (err < 0)
		return err;

	return 0;
}