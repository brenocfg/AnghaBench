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
 int /*<<< orphan*/  DP83865_INT_MASK_DEFAULT ; 
 int /*<<< orphan*/  DP83865_INT_MASK_REG ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ns_config_intr(struct phy_device *phydev)
{
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		err = phy_write(phydev, DP83865_INT_MASK_REG,
				DP83865_INT_MASK_DEFAULT);
	else
		err = phy_write(phydev, DP83865_INT_MASK_REG, 0);

	return err;
}