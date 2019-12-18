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
 int ENOMEM ; 
 int /*<<< orphan*/  proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_stat_proc_fops ; 

int
xfs_init_procfs(void)
{
	if (!proc_mkdir("fs/xfs", NULL))
		goto out;

	if (!proc_create("fs/xfs/stat", 0, NULL,
			 &xfs_stat_proc_fops))
		goto out_remove_entry;
	return 0;

 out_remove_entry:
	remove_proc_entry("fs/xfs", NULL);
 out:
	return -ENOMEM;
}