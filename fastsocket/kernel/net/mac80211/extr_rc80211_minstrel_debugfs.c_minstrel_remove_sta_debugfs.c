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
struct minstrel_sta_info {int /*<<< orphan*/  dbg_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void
minstrel_remove_sta_debugfs(void *priv, void *priv_sta)
{
	struct minstrel_sta_info *mi = priv_sta;

	debugfs_remove(mi->dbg_stats);
}