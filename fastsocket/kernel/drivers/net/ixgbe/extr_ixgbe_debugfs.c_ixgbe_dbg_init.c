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
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ixgbe_dbg_root ; 
 int /*<<< orphan*/  ixgbe_driver_name ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void ixgbe_dbg_init(void)
{
	ixgbe_dbg_root = debugfs_create_dir(ixgbe_driver_name, NULL);
	if (ixgbe_dbg_root == NULL)
		pr_err("init of debugfs failed\n");
}