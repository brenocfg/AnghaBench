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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int bus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  root_device_register (char*) ; 
 int /*<<< orphan*/  root_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_loop_driverfs ; 
 int /*<<< orphan*/  tcm_loop_lld_bus ; 
 int /*<<< orphan*/  tcm_loop_primary ; 

__attribute__((used)) static int tcm_loop_alloc_core_bus(void)
{
	int ret;

	tcm_loop_primary = root_device_register("tcm_loop_0");
	if (IS_ERR(tcm_loop_primary)) {
		pr_err("Unable to allocate tcm_loop_primary\n");
		return PTR_ERR(tcm_loop_primary);
	}

	ret = bus_register(&tcm_loop_lld_bus);
	if (ret) {
		pr_err("bus_register() failed for tcm_loop_lld_bus\n");
		goto dev_unreg;
	}

	ret = driver_register(&tcm_loop_driverfs);
	if (ret) {
		pr_err("driver_register() failed for"
				"tcm_loop_driverfs\n");
		goto bus_unreg;
	}

	pr_debug("Initialized TCM Loop Core Bus\n");
	return ret;

bus_unreg:
	bus_unregister(&tcm_loop_lld_bus);
dev_unreg:
	root_device_unregister(tcm_loop_primary);
	return ret;
}