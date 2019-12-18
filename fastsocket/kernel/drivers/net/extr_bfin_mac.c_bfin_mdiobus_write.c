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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int SET_PHYAD (scalar_t__) ; 
 int SET_REGAD (scalar_t__) ; 
 int STABUSY ; 
 int STAOP ; 
 int /*<<< orphan*/  bfin_mdio_poll () ; 
 int /*<<< orphan*/  bfin_write_EMAC_STAADD (int) ; 
 int /*<<< orphan*/  bfin_write_EMAC_STADAT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfin_mdiobus_write(struct mii_bus *bus, int phy_addr, int regnum,
			      u16 value)
{
	bfin_mdio_poll();

	bfin_write_EMAC_STADAT((u32) value);

	/* write mode */
	bfin_write_EMAC_STAADD(SET_PHYAD((u16) phy_addr) |
				SET_REGAD((u16) regnum) |
				STAOP |
				STABUSY);

	bfin_mdio_poll();

	return 0;
}