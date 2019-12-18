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
struct phy_device {int supported; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  phy_find_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_find_valid (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* settings ; 

void phy_sanitize_settings(struct phy_device *phydev)
{
	u32 features = phydev->supported;
	int idx;

	/* Sanitize settings based on PHY capabilities */
	if ((features & SUPPORTED_Autoneg) == 0)
		phydev->autoneg = AUTONEG_DISABLE;

	idx = phy_find_valid(phy_find_setting(phydev->speed, phydev->duplex),
			features);

	phydev->speed = settings[idx].speed;
	phydev->duplex = settings[idx].duplex;
}