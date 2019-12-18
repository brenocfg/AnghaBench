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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  debugfs_dir; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  add_ap_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_common_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_ibss_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_mesh_config (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_mesh_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_mesh_stats (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_sta_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  add_wds_files (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ap_power_level ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  txpower ; 
 int /*<<< orphan*/  user_power_level ; 

__attribute__((used)) static void add_files(struct ieee80211_sub_if_data *sdata)
{
	if (!sdata->vif.debugfs_dir)
		return;

	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(state);
	DEBUGFS_ADD(txpower);
	DEBUGFS_ADD(user_power_level);
	DEBUGFS_ADD(ap_power_level);

	if (sdata->vif.type != NL80211_IFTYPE_MONITOR)
		add_common_files(sdata);

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_MESH_POINT:
#ifdef CONFIG_MAC80211_MESH
		add_mesh_files(sdata);
		add_mesh_stats(sdata);
		add_mesh_config(sdata);
#endif
		break;
	case NL80211_IFTYPE_STATION:
		add_sta_files(sdata);
		break;
	case NL80211_IFTYPE_ADHOC:
		add_ibss_files(sdata);
		break;
	case NL80211_IFTYPE_AP:
		add_ap_files(sdata);
		break;
	case NL80211_IFTYPE_WDS:
		add_wds_files(sdata);
		break;
	default:
		break;
	}
}