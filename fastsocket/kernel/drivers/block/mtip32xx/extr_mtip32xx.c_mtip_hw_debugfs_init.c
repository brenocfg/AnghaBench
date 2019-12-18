#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct driver_data {int /*<<< orphan*/ * dfs_node; TYPE_1__* disk; TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/ * debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct driver_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfs_parent ; 
 int /*<<< orphan*/  mtip_flags_fops ; 
 int /*<<< orphan*/  mtip_regs_fops ; 

__attribute__((used)) static int mtip_hw_debugfs_init(struct driver_data *dd)
{
	if (!dfs_parent)
		return -1;

	dd->dfs_node = debugfs_create_dir(dd->disk->disk_name, dfs_parent);
	if (IS_ERR_OR_NULL(dd->dfs_node)) {
		dev_warn(&dd->pdev->dev,
			"Error creating node %s under debugfs\n",
						dd->disk->disk_name);
		dd->dfs_node = NULL;
		return -1;
	}

	debugfs_create_file("flags", S_IRUGO, dd->dfs_node, dd,
							&mtip_flags_fops);
	debugfs_create_file("registers", S_IRUGO, dd->dfs_node, dd,
							&mtip_regs_fops);

	return 0;
}