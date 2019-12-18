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
 int /*<<< orphan*/  MII_M1011_IEVENT ; 
 int MII_M1011_IMASK_INIT ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1121_did_interrupt(struct phy_device *phydev)
{
	int imask;

	imask = phy_read(phydev, MII_M1011_IEVENT);

	if (imask & MII_M1011_IMASK_INIT)
		return 1;

	return 0;
}