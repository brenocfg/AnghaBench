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
struct minstrel_ht_sta_priv {int /*<<< orphan*/  dbg_stats; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct minstrel_ht_sta_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minstrel_ht_stat_fops ; 

void
minstrel_ht_add_sta_debugfs(void *priv, void *priv_sta, struct dentry *dir)
{
	struct minstrel_ht_sta_priv *msp = priv_sta;

	msp->dbg_stats = debugfs_create_file("rc_stats", S_IRUGO, dir, msp,
			&minstrel_ht_stat_fops);
}