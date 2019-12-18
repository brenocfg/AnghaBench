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
typedef  int /*<<< orphan*/  u32 ;
struct sta_info {scalar_t__ plink_state; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_PLINK_BLOCKED ; 
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int /*<<< orphan*/  ieee80211_mps_local_status_update (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_mps_sta_status_update (struct sta_info*) ; 
 int /*<<< orphan*/  mesh_path_flush_by_nexthop (struct sta_info*) ; 
 int /*<<< orphan*/  mesh_plink_dec_estab_count (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static u32 __mesh_plink_deactivate(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	u32 changed = 0;

	if (sta->plink_state == NL80211_PLINK_ESTAB)
		changed = mesh_plink_dec_estab_count(sdata);
	sta->plink_state = NL80211_PLINK_BLOCKED;
	mesh_path_flush_by_nexthop(sta);

	ieee80211_mps_sta_status_update(sta);
	changed |= ieee80211_mps_local_status_update(sdata);

	return changed;
}