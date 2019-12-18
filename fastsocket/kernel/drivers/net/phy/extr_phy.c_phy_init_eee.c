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
struct phy_device {scalar_t__ duplex; scalar_t__ interface; int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; int /*<<< orphan*/  speed; } ;
struct TYPE_2__ {int setting; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_AN_EEE_LPABLE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int MDIO_PCS_CTRL1_CLKSTOP_EN ; 
 int /*<<< orphan*/  MDIO_PCS_EEE_ABLE ; 
 scalar_t__ PHY_INTERFACE_MODE_GMII ; 
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 int mmd_eee_adv_to_ethtool_adv_t (int) ; 
 int mmd_eee_cap_to_ethtool_sup_t (int) ; 
 int phy_find_setting (int /*<<< orphan*/ ,scalar_t__) ; 
 int phy_read_mmd_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read_status (struct phy_device*) ; 
 int /*<<< orphan*/  phy_write_mmd_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* settings ; 

int phy_init_eee(struct phy_device *phydev, bool clk_stop_enable)
{
	int ret = -EPROTONOSUPPORT;

	/* According to 802.3az,the EEE is supported only in full duplex-mode.
	 * Also EEE feature is active when core is operating with MII, GMII
	 * or RGMII.
	 */
	if ((phydev->duplex == DUPLEX_FULL) &&
	    ((phydev->interface == PHY_INTERFACE_MODE_MII) ||
	    (phydev->interface == PHY_INTERFACE_MODE_GMII) ||
	    (phydev->interface == PHY_INTERFACE_MODE_RGMII))) {
		int eee_lp, eee_cap, eee_adv;
		u32 lp, cap, adv;
		int idx, status;

		/* Read phy status to properly get the right settings */
		status = phy_read_status(phydev);
		if (status)
			return status;

		/* First check if the EEE ability is supported */
		eee_cap = phy_read_mmd_indirect(phydev->bus, MDIO_PCS_EEE_ABLE,
						MDIO_MMD_PCS, phydev->addr);
		if (eee_cap < 0)
			return eee_cap;

		cap = mmd_eee_cap_to_ethtool_sup_t(eee_cap);
		if (!cap)
			goto eee_exit;

		/* Check which link settings negotiated and verify it in
		 * the EEE advertising registers.
		 */
		eee_lp = phy_read_mmd_indirect(phydev->bus, MDIO_AN_EEE_LPABLE,
					       MDIO_MMD_AN, phydev->addr);
		if (eee_lp < 0)
			return eee_lp;

		eee_adv = phy_read_mmd_indirect(phydev->bus, MDIO_AN_EEE_ADV,
						MDIO_MMD_AN, phydev->addr);
		if (eee_adv < 0)
			return eee_adv;

		adv = mmd_eee_adv_to_ethtool_adv_t(eee_adv);
		lp = mmd_eee_adv_to_ethtool_adv_t(eee_lp);
		idx = phy_find_setting(phydev->speed, phydev->duplex);
		if (!(lp & adv & settings[idx].setting))
			goto eee_exit;

		if (clk_stop_enable) {
			/* Configure the PHY to stop receiving xMII
			 * clock while it is signaling LPI.
			 */
			int val = phy_read_mmd_indirect(phydev->bus, MDIO_CTRL1,
							MDIO_MMD_PCS,
							phydev->addr);
			if (val < 0)
				return val;

			val |= MDIO_PCS_CTRL1_CLKSTOP_EN;
			phy_write_mmd_indirect(phydev->bus, MDIO_CTRL1,
					       MDIO_MMD_PCS, phydev->addr, val);
		}

		ret = 0; /* EEE supported */
	}

eee_exit:
	return ret;
}