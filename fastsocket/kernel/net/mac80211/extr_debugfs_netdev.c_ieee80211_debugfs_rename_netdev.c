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
struct TYPE_2__ {struct dentry* debugfs_dir; } ;
struct ieee80211_sub_if_data {char* name; TYPE_1__ vif; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  debugfs_rename (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdata_err (struct ieee80211_sub_if_data*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void ieee80211_debugfs_rename_netdev(struct ieee80211_sub_if_data *sdata)
{
	struct dentry *dir;
	char buf[10 + IFNAMSIZ];

	dir = sdata->vif.debugfs_dir;

	if (!dir)
		return;

	sprintf(buf, "netdev:%s", sdata->name);
	if (!debugfs_rename(dir->d_parent, dir, dir->d_parent, buf))
		sdata_err(sdata,
			  "debugfs: failed to rename debugfs dir to %s\n",
			  buf);
}