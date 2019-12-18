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
struct phy_device {scalar_t__ interrupts; TYPE_1__* drv; } ;
struct TYPE_2__ {scalar_t__ phy_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_VSC8221_IMASK_MASK ; 
 int /*<<< orphan*/  MII_VSC8244_IMASK ; 
 int /*<<< orphan*/  MII_VSC8244_IMASK_MASK ; 
 int /*<<< orphan*/  MII_VSC8244_ISTAT ; 
 scalar_t__ PHY_ID_VSC8244 ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc82xx_config_intr(struct phy_device *phydev)
{
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		err = phy_write(phydev, MII_VSC8244_IMASK,
			phydev->drv->phy_id == PHY_ID_VSC8244 ?
				MII_VSC8244_IMASK_MASK :
				MII_VSC8221_IMASK_MASK);
	else {
		/*
		 * The Vitesse PHY cannot clear the interrupt
		 * once it has disabled them, so we clear them first
		 */
		err = phy_read(phydev, MII_VSC8244_ISTAT);

		if (err < 0)
			return err;

		err = phy_write(phydev, MII_VSC8244_IMASK, 0);
	}

	return err;
}