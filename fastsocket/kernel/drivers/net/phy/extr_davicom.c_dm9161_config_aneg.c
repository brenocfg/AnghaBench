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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_ISOLATE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int genphy_config_aneg (struct phy_device*) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm9161_config_aneg(struct phy_device *phydev)
{
	int err;

	/* Isolate the PHY */
	err = phy_write(phydev, MII_BMCR, BMCR_ISOLATE);

	if (err < 0)
		return err;

	/* Configure the new settings */
	err = genphy_config_aneg(phydev);

	if (err < 0)
		return err;

	return 0;
}