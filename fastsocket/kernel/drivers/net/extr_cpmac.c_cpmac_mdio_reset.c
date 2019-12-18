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
struct mii_bus {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7_RESET_BIT_MDIO ; 
 int /*<<< orphan*/  CPMAC_MDIO_CONTROL ; 
 int MDIOC_CLKDIV (int) ; 
 int MDIOC_ENABLE ; 
 int ar7_cpmac_freq () ; 
 int /*<<< orphan*/  ar7_device_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpmac_mdio_reset(struct mii_bus *bus)
{
	ar7_device_reset(AR7_RESET_BIT_MDIO);
	cpmac_write(bus->priv, CPMAC_MDIO_CONTROL, MDIOC_ENABLE |
		    MDIOC_CLKDIV(ar7_cpmac_freq() / 2200000 - 1));
	return 0;
}