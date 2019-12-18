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
typedef  size_t u8 ;
typedef  int u32 ;
struct iwl_scale_tbl_info {int ant_type; int current_rate; } ;
struct iwl_mvm {int /*<<< orphan*/  fw; } ;
struct iwl_lq_sta {int last_txrate_idx; size_t active_tbl; int /*<<< orphan*/  lq; struct iwl_scale_tbl_info* lq_info; int /*<<< orphan*/  search_better_tbl; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_2__ {int plcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int IWL_FIRST_CCK_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_RATE_COUNT ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int first_antenna (size_t) ; 
 size_t iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_send_lq_cmd (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* iwl_rates ; 
 int rate_n_flags_from_tbl (struct iwl_mvm*,struct iwl_scale_tbl_info*,int,size_t) ; 
 int /*<<< orphan*/  rs_fill_link_cmd (int /*<<< orphan*/ *,struct iwl_lq_sta*,int) ; 
 int /*<<< orphan*/  rs_get_tbl_info_from_mcs (int,int,struct iwl_scale_tbl_info*,int*) ; 
 int /*<<< orphan*/  rs_is_valid_ant (size_t,int) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int /*<<< orphan*/  rs_toggle_antenna (size_t,int*,struct iwl_scale_tbl_info*) ; 
 size_t rs_use_green (struct ieee80211_sta*) ; 

__attribute__((used)) static void rs_initialize_lq(struct iwl_mvm *mvm,
			     struct ieee80211_sta *sta,
			     struct iwl_lq_sta *lq_sta,
			     enum ieee80211_band band)
{
	struct iwl_scale_tbl_info *tbl;
	int rate_idx;
	int i;
	u32 rate;
	u8 use_green = rs_use_green(sta);
	u8 active_tbl = 0;
	u8 valid_tx_ant;

	if (!sta || !lq_sta)
		return;

	i = lq_sta->last_txrate_idx;

	valid_tx_ant = iwl_fw_valid_tx_ant(mvm->fw);

	if (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	else
		active_tbl = 1 - lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	if ((i < 0) || (i >= IWL_RATE_COUNT))
		i = 0;

	rate = iwl_rates[i].plcp;
	tbl->ant_type = first_antenna(valid_tx_ant);
	rate |= tbl->ant_type << RATE_MCS_ANT_POS;

	if (i >= IWL_FIRST_CCK_RATE && i <= IWL_LAST_CCK_RATE)
		rate |= RATE_MCS_CCK_MSK;

	rs_get_tbl_info_from_mcs(rate, band, tbl, &rate_idx);
	if (!rs_is_valid_ant(valid_tx_ant, tbl->ant_type))
		rs_toggle_antenna(valid_tx_ant, &rate, tbl);

	rate = rate_n_flags_from_tbl(mvm, tbl, rate_idx, use_green);
	tbl->current_rate = rate;
	rs_set_expected_tpt_table(lq_sta, tbl);
	rs_fill_link_cmd(NULL, lq_sta, rate);
	/* TODO restore station should remember the lq cmd */
	iwl_mvm_send_lq_cmd(mvm, &lq_sta->lq, CMD_SYNC, true);
}