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
struct mii_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BCM5201_INTERRUPT ; 
 int /*<<< orphan*/  MII_BCM5201_MULTIPHY ; 
 int /*<<< orphan*/  MII_BCM5201_MULTIPHY_SUPERISOLATE ; 
 int /*<<< orphan*/  phy_write (struct mii_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm5201_suspend(struct mii_phy* phy)
{
	phy_write(phy, MII_BCM5201_INTERRUPT, 0);
	phy_write(phy, MII_BCM5201_MULTIPHY, MII_BCM5201_MULTIPHY_SUPERISOLATE);

	return 0;
}