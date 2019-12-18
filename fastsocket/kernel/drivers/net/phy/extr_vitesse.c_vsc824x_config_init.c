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
 int MII_VSC8244_AUXCONSTAT_INIT ; 
 int /*<<< orphan*/  MII_VSC8244_AUX_CONSTAT ; 
 int MII_VSC8244_EXTCON1_RX_SKEW ; 
 int MII_VSC8244_EXTCON1_RX_SKEW_MASK ; 
 int MII_VSC8244_EXTCON1_TX_SKEW ; 
 int MII_VSC8244_EXTCON1_TX_SKEW_MASK ; 
 int /*<<< orphan*/  MII_VSC8244_EXT_CON1 ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc824x_config_init(struct phy_device *phydev)
{
	int extcon;
	int err;

	err = phy_write(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8244_AUXCONSTAT_INIT);
	if (err < 0)
		return err;

	extcon = phy_read(phydev, MII_VSC8244_EXT_CON1);

	if (extcon < 0)
		return err;

	extcon &= ~(MII_VSC8244_EXTCON1_TX_SKEW_MASK |
			MII_VSC8244_EXTCON1_RX_SKEW_MASK);

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID)
		extcon |= (MII_VSC8244_EXTCON1_TX_SKEW |
				MII_VSC8244_EXTCON1_RX_SKEW);

	err = phy_write(phydev, MII_VSC8244_EXT_CON1, extcon);

	return err;
}