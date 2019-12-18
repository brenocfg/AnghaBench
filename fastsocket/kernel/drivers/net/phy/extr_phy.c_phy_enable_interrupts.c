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
 int /*<<< orphan*/  PHY_INTERRUPT_ENABLED ; 
 int phy_clear_interrupt (struct phy_device*) ; 
 int phy_config_interrupt (struct phy_device*,int /*<<< orphan*/ ) ; 

int phy_enable_interrupts(struct phy_device *phydev)
{
	int err;

	err = phy_clear_interrupt(phydev);

	if (err < 0)
		return err;

	err = phy_config_interrupt(phydev, PHY_INTERRUPT_ENABLED);

	return err;
}