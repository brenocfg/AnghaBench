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
struct phy_device {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int ip175c_config_aneg(struct phy_device *phydev)
{
	if (phydev->addr == 4) /* WAN port */
		genphy_config_aneg(phydev);

	return 0;
}