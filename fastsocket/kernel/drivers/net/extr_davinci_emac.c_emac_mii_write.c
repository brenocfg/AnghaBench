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
typedef  int u16 ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_USERACCESS (int /*<<< orphan*/ ) ; 
 int MDIO_USERACCESS_DATA ; 
 int MDIO_USERACCESS_GO ; 
 int MDIO_USERACCESS_PHYADR ; 
 int MDIO_USERACCESS_REGADR ; 
 int MDIO_USERACCESS_WRITE ; 
 int /*<<< orphan*/  MDIO_WAIT_FOR_USER_ACCESS ; 
 int /*<<< orphan*/  emac_mdio_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int emac_mii_write(struct mii_bus *bus, int phy_id,
			  int phy_reg, u16 phy_data)
{

	unsigned int control;

	/*  until mdio is ready for next command */
	MDIO_WAIT_FOR_USER_ACCESS;

	control = (MDIO_USERACCESS_GO |
		   MDIO_USERACCESS_WRITE |
		   ((phy_reg << 21) & MDIO_USERACCESS_REGADR) |
		   ((phy_id << 16) & MDIO_USERACCESS_PHYADR) |
		   (phy_data & MDIO_USERACCESS_DATA));
	emac_mdio_write(MDIO_USERACCESS(0), control);

	return 0;
}