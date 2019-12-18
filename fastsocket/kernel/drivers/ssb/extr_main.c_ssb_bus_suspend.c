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
struct ssb_bus {int /*<<< orphan*/  chipco; } ;

/* Variables and functions */
 int SSB_GPIO_PLL ; 
 int SSB_GPIO_XTAL ; 
 int /*<<< orphan*/  ssb_chipco_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_pci_xtal (struct ssb_bus*,int,int /*<<< orphan*/ ) ; 

int ssb_bus_suspend(struct ssb_bus *bus)
{
	ssb_chipco_suspend(&bus->chipco);
	ssb_pci_xtal(bus, SSB_GPIO_XTAL | SSB_GPIO_PLL, 0);

	return 0;
}