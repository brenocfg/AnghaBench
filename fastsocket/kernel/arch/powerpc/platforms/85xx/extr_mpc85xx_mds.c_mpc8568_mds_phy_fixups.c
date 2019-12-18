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
 int phy_read (struct phy_device*,int) ; 
 int phy_write (struct phy_device*,int,int) ; 

__attribute__((used)) static int mpc8568_mds_phy_fixups(struct phy_device *phydev)
{
	int temp;
	int err;

	/* Errata */
	err = phy_write(phydev,29, 0x0006);

	if (err)
		return err;

	temp = phy_read(phydev, 30);

	if (temp < 0)
		return temp;

	temp = (temp & (~0x8000)) | 0x4000;
	err = phy_write(phydev,30, temp);

	if (err)
		return err;

	err = phy_write(phydev,29, 0x000a);

	if (err)
		return err;

	temp = phy_read(phydev, 30);

	if (temp < 0)
		return temp;

	temp = phy_read(phydev, 30);

	if (temp < 0)
		return temp;

	temp &= ~0x0020;

	err = phy_write(phydev,30,temp);

	if (err)
		return err;

	/* Disable automatic MDI/MDIX selection */
	temp = phy_read(phydev, 16);

	if (temp < 0)
		return temp;

	temp &= ~0x0060;
	err = phy_write(phydev,16,temp);

	return err;
}