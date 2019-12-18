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
struct pktcdvd_device {int /*<<< orphan*/ * dfs_d_root; int /*<<< orphan*/ * dfs_f_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_debugfs_root ; 

__attribute__((used)) static void pkt_debugfs_dev_remove(struct pktcdvd_device *pd)
{
	if (!pkt_debugfs_root)
		return;
	if (pd->dfs_f_info)
		debugfs_remove(pd->dfs_f_info);
	pd->dfs_f_info = NULL;
	if (pd->dfs_d_root)
		debugfs_remove(pd->dfs_d_root);
	pd->dfs_d_root = NULL;
}