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
struct mii_bus {int /*<<< orphan*/  (* write ) (struct mii_bus*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MII_MMD_CTRL ; 
 int MII_MMD_CTRL_NOINCR ; 
 int /*<<< orphan*/  MII_MMD_DATA ; 
 int /*<<< orphan*/  stub1 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mmd_phy_indirect(struct mii_bus *bus, int prtad, int devad,
				    int addr)
{
	/* Write the desired MMD Devad */
	bus->write(bus, addr, MII_MMD_CTRL, devad);

	/* Write the desired MMD register address */
	bus->write(bus, addr, MII_MMD_DATA, prtad);

	/* Select the Function : DATA with no post increment */
	bus->write(bus, addr, MII_MMD_CTRL, (devad | MII_MMD_CTRL_NOINCR));
}