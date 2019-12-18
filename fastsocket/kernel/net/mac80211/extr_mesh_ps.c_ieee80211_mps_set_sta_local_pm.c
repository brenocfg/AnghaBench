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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct sta_info {int local_pm; scalar_t__ plink_state; TYPE_1__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {int dummy; } ;
typedef  enum nl80211_mesh_power_mode { ____Placeholder_nl80211_mesh_power_mode } nl80211_mesh_power_mode ;

/* Variables and functions */
 scalar_t__ NL80211_PLINK_ESTAB ; 
 int /*<<< orphan*/  ieee80211_mps_local_status_update (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mps_dbg (struct ieee80211_sub_if_data*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_qos_null_tx (struct sta_info*) ; 

u32 ieee80211_mps_set_sta_local_pm(struct sta_info *sta,
				   enum nl80211_mesh_power_mode pm)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;

	mps_dbg(sdata, "local STA operates in mode %d with %pM\n",
		pm, sta->sta.addr);

	sta->local_pm = pm;

	/*
	 * announce peer-specific power mode transition
	 * (see IEEE802.11-2012 13.14.3.2 and 13.14.3.3)
	 */
	if (sta->plink_state == NL80211_PLINK_ESTAB)
		mps_qos_null_tx(sta);

	return ieee80211_mps_local_status_update(sdata);
}