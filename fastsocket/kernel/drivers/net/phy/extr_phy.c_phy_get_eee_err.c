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

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_PCS_EEE_WK_ERR ; 
 int phy_read_mmd_indirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phy_get_eee_err(struct phy_device *phydev)
{
	return phy_read_mmd_indirect(phydev->bus, MDIO_PCS_EEE_WK_ERR,
				     MDIO_MMD_PCS, phydev->addr);

}