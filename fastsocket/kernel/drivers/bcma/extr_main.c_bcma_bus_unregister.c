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
struct bcma_device {int dummy; } ;
struct bcma_bus {int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_CORE_4706_MAC_GBIT_COMMON ; 
 int /*<<< orphan*/  BCMA_CORE_MIPS_74K ; 
 int /*<<< orphan*/  BCMA_CORE_PCIE ; 
 int EBUSY ; 
 int /*<<< orphan*/  bcma_err (struct bcma_bus*,char*,...) ; 
 struct bcma_device* bcma_find_core (struct bcma_bus*,int /*<<< orphan*/ ) ; 
 int bcma_gpio_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcma_unregister_cores (struct bcma_bus*) ; 
 int /*<<< orphan*/  kfree (struct bcma_device*) ; 

void bcma_bus_unregister(struct bcma_bus *bus)
{
	struct bcma_device *cores[3];
	int err;

	err = bcma_gpio_unregister(&bus->drv_cc);
	if (err == -EBUSY)
		bcma_err(bus, "Some GPIOs are still in use.\n");
	else if (err)
		bcma_err(bus, "Can not unregister GPIO driver: %i\n", err);

	cores[0] = bcma_find_core(bus, BCMA_CORE_MIPS_74K);
	cores[1] = bcma_find_core(bus, BCMA_CORE_PCIE);
	cores[2] = bcma_find_core(bus, BCMA_CORE_4706_MAC_GBIT_COMMON);

	bcma_unregister_cores(bus);

	kfree(cores[2]);
	kfree(cores[1]);
	kfree(cores[0]);
}