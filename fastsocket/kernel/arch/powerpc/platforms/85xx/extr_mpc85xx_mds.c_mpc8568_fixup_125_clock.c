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
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MV88E1111_SCR ; 
 int MV88E1111_SCR_125CLK ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpc8568_fixup_125_clock(struct phy_device *phydev)
{
	int scr;
	int err;

	/* Workaround for the 125 CLK Toggle */
	scr = phy_read(phydev, MV88E1111_SCR);

	if (scr < 0)
		return scr;

	err = phy_write(phydev, MV88E1111_SCR, scr & ~(MV88E1111_SCR_125CLK));

	if (err)
		return err;

	err = phy_write(phydev, MII_BMCR, BMCR_RESET);

	if (err)
		return err;

	scr = phy_read(phydev, MV88E1111_SCR);

	if (scr < 0)
		return err;

	err = phy_write(phydev, MV88E1111_SCR, scr | 0x0008);

	return err;
}