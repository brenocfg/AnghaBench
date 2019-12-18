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
 int /*<<< orphan*/  proc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xqm_proc_fops ; 
 int /*<<< orphan*/  xqmstat_proc_fops ; 

void
xfs_qm_init_procfs(void)
{
	proc_create("fs/xfs/xqmstat", 0, NULL, &xqmstat_proc_fops);
	proc_create("fs/xfs/xqm", 0, NULL, &xqm_proc_fops);
}