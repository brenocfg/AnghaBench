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
typedef  int u8 ;
typedef  int u16 ;
struct iwl_scale_tbl_info {int is_ht40; int current_rate; scalar_t__ is_SGI; int /*<<< orphan*/  max_search; scalar_t__ action; int /*<<< orphan*/  lq_type; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {int is_green; int active_siso_rate; } ;
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_MAX_SEARCH ; 
 int IWL_RATE_INVALID ; 
 int /*<<< orphan*/  LQ_SISO ; 
 scalar_t__ iwl_is_ht40_tx_allowed (struct ieee80211_sta*) ; 
 int rate_n_flags_from_tbl (struct iwl_mvm*,struct iwl_scale_tbl_info*,int,int) ; 
 int rs_get_best_rate (struct iwl_mvm*,struct iwl_lq_sta*,struct iwl_scale_tbl_info*,int,int) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 

__attribute__((used)) static int rs_switch_to_siso(struct iwl_mvm *mvm,
			     struct iwl_lq_sta *lq_sta,
			     struct ieee80211_sta *sta,
			     struct iwl_scale_tbl_info *tbl, int index)
{
	u16 rate_mask;
	u8 is_green = lq_sta->is_green;
	s32 rate;

	if (!sta->ht_cap.ht_supported)
		return -1;

	IWL_DEBUG_RATE(mvm, "LQ: try to switch to SISO\n");

	tbl->lq_type = LQ_SISO;
	tbl->action = 0;
	tbl->max_search = IWL_MAX_SEARCH;
	rate_mask = lq_sta->active_siso_rate;

	if (iwl_is_ht40_tx_allowed(sta))
		tbl->is_ht40 = 1;
	else
		tbl->is_ht40 = 0;

	if (is_green)
		tbl->is_SGI = 0; /*11n spec: no SGI in SISO+Greenfield*/

	rs_set_expected_tpt_table(lq_sta, tbl);
	rate = rs_get_best_rate(mvm, lq_sta, tbl, rate_mask, index);

	IWL_DEBUG_RATE(mvm, "LQ: get best rate %d mask %X\n", rate, rate_mask);
	if ((rate == IWL_RATE_INVALID) || !((1 << rate) & rate_mask)) {
		IWL_DEBUG_RATE(mvm,
			       "can not switch with index %d rate mask %x\n",
			       rate, rate_mask);
		return -1;
	}
	tbl->current_rate = rate_n_flags_from_tbl(mvm, tbl, rate, is_green);
	IWL_DEBUG_RATE(mvm, "LQ: Switch to new mcs %X index is green %X\n",
		       tbl->current_rate, is_green);
	return 0;
}