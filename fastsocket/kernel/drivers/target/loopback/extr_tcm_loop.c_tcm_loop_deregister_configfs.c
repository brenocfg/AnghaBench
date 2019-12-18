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
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  target_fabric_configfs_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcm_loop_fabric_configfs ; 

__attribute__((used)) static void tcm_loop_deregister_configfs(void)
{
	if (!tcm_loop_fabric_configfs)
		return;

	target_fabric_configfs_deregister(tcm_loop_fabric_configfs);
	tcm_loop_fabric_configfs = NULL;
	pr_debug("TCM_LOOP[0] - Cleared"
				" tcm_loop_fabric_configfs\n");
}