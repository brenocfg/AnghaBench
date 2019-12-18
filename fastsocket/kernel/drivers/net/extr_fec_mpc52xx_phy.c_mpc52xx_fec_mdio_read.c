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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_MII_READ_FRAME ; 
 int mpc52xx_fec_mdio_transfer (struct mii_bus*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc52xx_fec_mdio_read(struct mii_bus *bus, int phy_id, int reg)
{
	return mpc52xx_fec_mdio_transfer(bus, phy_id, reg, FEC_MII_READ_FRAME);
}