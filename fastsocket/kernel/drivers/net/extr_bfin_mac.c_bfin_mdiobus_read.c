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
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int SET_PHYAD (int /*<<< orphan*/ ) ; 
 int SET_REGAD (int /*<<< orphan*/ ) ; 
 int STABUSY ; 
 int /*<<< orphan*/  bfin_mdio_poll () ; 
 scalar_t__ bfin_read_EMAC_STADAT () ; 
 int /*<<< orphan*/  bfin_write_EMAC_STAADD (int) ; 

__attribute__((used)) static int bfin_mdiobus_read(struct mii_bus *bus, int phy_addr, int regnum)
{
	bfin_mdio_poll();

	/* read mode */
	bfin_write_EMAC_STAADD(SET_PHYAD((u16) phy_addr) |
				SET_REGAD((u16) regnum) |
				STABUSY);

	bfin_mdio_poll();

	return (int) bfin_read_EMAC_STADAT();
}