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
struct phy_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;
struct ethtool_eee {int /*<<< orphan*/  advertised; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int ethtool_adv_to_mmd_eee_adv_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int phy_ethtool_set_eee(struct phy_device *phydev, struct ethtool_eee *data)
{
	int val;

	val = ethtool_adv_to_mmd_eee_adv_t(data->advertised);
	phy_write_mmd_indirect(phydev->bus, MDIO_AN_EEE_ADV, MDIO_MMD_AN,
			       phydev->addr, val);

	return 0;
}