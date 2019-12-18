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
 int /*<<< orphan*/  MII_VSC8221_AUXCONSTAT_INIT ; 
 int /*<<< orphan*/  MII_VSC8244_AUX_CONSTAT ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc8221_config_init(struct phy_device *phydev)
{
	int err;

	err = phy_write(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8221_AUXCONSTAT_INIT);
	return err;

	/* Perhaps we should set EXT_CON1 based on the interface?
	   Options are 802.3Z SerDes or SGMII */
}