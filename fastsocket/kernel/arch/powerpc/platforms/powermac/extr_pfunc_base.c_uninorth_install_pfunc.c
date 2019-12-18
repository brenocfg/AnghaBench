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
struct device_node {int /*<<< orphan*/  full_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMF_FLAGS_ON_INIT ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  pmf_do_functions (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_register_driver (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 struct device_node* unin_hwclock ; 
 int /*<<< orphan*/  unin_mmio_handlers ; 
 struct device_node* uninorth_node ; 

__attribute__((used)) static void uninorth_install_pfunc(void)
{
	struct device_node *np;

	DBG("Installing functions for UniN %s\n",
	    uninorth_node->full_name);

	/*
	 * Install handlers for the bridge itself
	 */
	pmf_register_driver(uninorth_node, &unin_mmio_handlers, NULL);
	pmf_do_functions(uninorth_node, NULL, 0, PMF_FLAGS_ON_INIT, NULL);


	/*
	 * Install handlers for the hwclock child if any
	 */
	for (np = NULL; (np = of_get_next_child(uninorth_node, np)) != NULL;)
		if (strcmp(np->name, "hw-clock") == 0) {
			unin_hwclock = np;
			break;
		}
	if (unin_hwclock) {
		DBG("Installing functions for UniN clock %s\n",
		    unin_hwclock->full_name);
		pmf_register_driver(unin_hwclock, &unin_mmio_handlers, NULL);
		pmf_do_functions(unin_hwclock, NULL, 0, PMF_FLAGS_ON_INIT,
				 NULL);
	}
}