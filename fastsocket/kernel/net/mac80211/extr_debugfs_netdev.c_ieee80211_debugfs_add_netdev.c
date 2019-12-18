#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* debugfs_dir; } ;
struct TYPE_6__ {void* subdir_stations; } ;
struct ieee80211_sub_if_data {char* name; TYPE_2__ vif; TYPE_1__ debugfs; TYPE_5__* local; } ;
struct TYPE_9__ {TYPE_3__* wiphy; } ;
struct TYPE_10__ {TYPE_4__ hw; } ;
struct TYPE_8__ {void* debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  add_files (struct ieee80211_sub_if_data*) ; 
 void* debugfs_create_dir (char*,void*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void ieee80211_debugfs_add_netdev(struct ieee80211_sub_if_data *sdata)
{
	char buf[10+IFNAMSIZ];

	sprintf(buf, "netdev:%s", sdata->name);
	sdata->vif.debugfs_dir = debugfs_create_dir(buf,
		sdata->local->hw.wiphy->debugfsdir);
	if (sdata->vif.debugfs_dir)
		sdata->debugfs.subdir_stations = debugfs_create_dir("stations",
			sdata->vif.debugfs_dir);
	add_files(sdata);
}