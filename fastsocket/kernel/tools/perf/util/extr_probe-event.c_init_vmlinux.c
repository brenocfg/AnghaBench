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
struct TYPE_2__ {int sort_by_name; int try_vmlinux_path; int /*<<< orphan*/ * vmlinux_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_KERNEL_ID ; 
 int /*<<< orphan*/  machine ; 
 scalar_t__ machine__create_kernel_maps (int /*<<< orphan*/ *) ; 
 int machine__init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int symbol__init () ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int init_vmlinux(void)
{
	int ret;

	symbol_conf.sort_by_name = true;
	if (symbol_conf.vmlinux_name == NULL)
		symbol_conf.try_vmlinux_path = true;
	else
		pr_debug("Use vmlinux: %s\n", symbol_conf.vmlinux_name);
	ret = symbol__init();
	if (ret < 0) {
		pr_debug("Failed to init symbol map.\n");
		goto out;
	}

	ret = machine__init(&machine, "", HOST_KERNEL_ID);
	if (ret < 0)
		goto out;

	if (machine__create_kernel_maps(&machine) < 0) {
		pr_debug("machine__create_kernel_maps() failed.\n");
		goto out;
	}
out:
	if (ret < 0)
		pr_warning("Failed to init vmlinux path.\n");
	return ret;
}