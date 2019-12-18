#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct machine {int /*<<< orphan*/  kmaps; int /*<<< orphan*/  pid; } ;
struct dso {int dummy; } ;
struct TYPE_2__ {scalar_t__ use_modules; } ;

/* Variables and functions */
 scalar_t__ __machine__create_kernel_maps (struct machine*,struct dso*) ; 
 scalar_t__ machine__create_modules (struct machine*) ; 
 struct dso* machine__get_kernel (struct machine*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 int /*<<< orphan*/  map_groups__fixup_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 TYPE_1__ symbol_conf ; 

int machine__create_kernel_maps(struct machine *machine)
{
	struct dso *kernel = machine__get_kernel(machine);

	if (kernel == NULL ||
	    __machine__create_kernel_maps(machine, kernel) < 0)
		return -1;

	if (symbol_conf.use_modules && machine__create_modules(machine) < 0) {
		if (machine__is_host(machine))
			pr_debug("Problems creating module maps, "
				 "continuing anyway...\n");
		else
			pr_debug("Problems creating module maps for guest %d, "
				 "continuing anyway...\n", machine->pid);
	}

	/*
	 * Now that we have all the maps created, just set the ->end of them:
	 */
	map_groups__fixup_end(&machine->kmaps);
	return 0;
}