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
 int /*<<< orphan*/  MDIO_CONTROL ; 
 unsigned int MDIO_CONTROL_CLKDIV ; 
 unsigned int MDIO_CONTROL_ENABLE ; 
 int emac_bus_frequency ; 
 int /*<<< orphan*/  emac_mdio_write (int /*<<< orphan*/ ,unsigned int) ; 
 int mdio_max_freq ; 

__attribute__((used)) static int emac_mii_reset(struct mii_bus *bus)
{
	unsigned int clk_div;
	int mdio_bus_freq = emac_bus_frequency;

	if (mdio_max_freq & mdio_bus_freq)
		clk_div = ((mdio_bus_freq / mdio_max_freq) - 1);
	else
		clk_div = 0xFF;

	clk_div &= MDIO_CONTROL_CLKDIV;

	/* Set enable and clock divider in MDIOControl */
	emac_mdio_write(MDIO_CONTROL, (clk_div | MDIO_CONTROL_ENABLE));

	return 0;

}