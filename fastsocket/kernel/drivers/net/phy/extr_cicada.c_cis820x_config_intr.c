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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CIS8201_IMASK ; 
 int /*<<< orphan*/  MII_CIS8201_IMASK_MASK ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cis820x_config_intr(struct phy_device *phydev)
{
	int err;

	if(phydev->interrupts == PHY_INTERRUPT_ENABLED)
		err = phy_write(phydev, MII_CIS8201_IMASK, 
				MII_CIS8201_IMASK_MASK);
	else
		err = phy_write(phydev, MII_CIS8201_IMASK, 0);

	return err;
}