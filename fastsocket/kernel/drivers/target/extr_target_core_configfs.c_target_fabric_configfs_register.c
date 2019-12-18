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
struct target_fabric_configfs {int /*<<< orphan*/  tf_subsys; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int target_fabric_tf_ops_check (struct target_fabric_configfs*) ; 

int target_fabric_configfs_register(
	struct target_fabric_configfs *tf)
{
	int ret;

	if (!tf) {
		pr_err("Unable to locate target_fabric_configfs"
			" pointer\n");
		return -EINVAL;
	}
	if (!tf->tf_subsys) {
		pr_err("Unable to target struct config_subsystem"
			" pointer\n");
		return -EINVAL;
	}
	ret = target_fabric_tf_ops_check(tf);
	if (ret < 0)
		return ret;

	pr_debug("<<<<<<<<<<<<<<<<<<<<<< END FABRIC API >>>>>>>>>>>>"
		">>>>>>>>>>\n");
	return 0;
}