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
typedef  int u8 ;
typedef  int u32 ;
struct iwl_scale_tbl_info {int action; int is_SGI; int* expected_tpt; int /*<<< orphan*/  lq_type; int /*<<< orphan*/  ant_type; int /*<<< orphan*/  current_rate; int /*<<< orphan*/  is_ht40; struct iwl_rate_scale_data* win; } ;
struct iwl_rate_scale_data {int /*<<< orphan*/  success_ratio; } ;
struct iwl_mvm {int /*<<< orphan*/  fw; } ;
struct iwl_lq_sta {size_t active_tbl; int last_tpt; int search_better_tbl; int /*<<< orphan*/  action_counter; struct iwl_scale_tbl_info* lq_info; int /*<<< orphan*/  is_green; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct ieee80211_sta {struct ieee80211_sta_ht_cap ht_cap; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_A ; 
 int /*<<< orphan*/  ANT_ABC ; 
 int /*<<< orphan*/  ANT_B ; 
 int /*<<< orphan*/  ANT_C ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
#define  IWL_MIMO2_SWITCH_ANTENNA1 134 
#define  IWL_MIMO2_SWITCH_ANTENNA2 133 
#define  IWL_MIMO2_SWITCH_GI 132 
#define  IWL_MIMO2_SWITCH_MIMO3_ABC 131 
#define  IWL_MIMO2_SWITCH_SISO_A 130 
#define  IWL_MIMO2_SWITCH_SISO_B 129 
#define  IWL_MIMO2_SWITCH_SISO_C 128 
 int IWL_RATE_COUNT ; 
 int /*<<< orphan*/  IWL_RS_GOOD_RATIO ; 
 int /*<<< orphan*/  LQ_NONE ; 
 int iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct iwl_scale_tbl_info*,struct iwl_scale_tbl_info*,int) ; 
 int num_of_ant (int) ; 
 int /*<<< orphan*/  rate_n_flags_from_tbl (struct iwl_mvm*,struct iwl_scale_tbl_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_is_valid_ant (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int rs_switch_to_mimo3 (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int rs_switch_to_siso (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  rs_toggle_antenna (int,int /*<<< orphan*/ *,struct iwl_scale_tbl_info*) ; 

__attribute__((used)) static int rs_move_mimo2_to_other(struct iwl_mvm *mvm,
				 struct iwl_lq_sta *lq_sta,
				 struct ieee80211_sta *sta, int index)
{
	s8 is_green = lq_sta->is_green;
	struct iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	struct iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	struct iwl_rate_scale_data *window = &(tbl->win[index]);
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	u32 sz = (sizeof(struct iwl_scale_tbl_info) -
		  (sizeof(struct iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = iwl_fw_valid_tx_ant(mvm->fw);
	u8 tx_chains_num = num_of_ant(valid_tx_ant);
	u8 update_search_tbl_counter = 0;
	int ret;

	start_action = tbl->action;
	while (1) {
		lq_sta->action_counter++;
		switch (tbl->action) {
		case IWL_MIMO2_SWITCH_ANTENNA1:
		case IWL_MIMO2_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(mvm, "LQ: MIMO2 toggle Antennas\n");

			if (tx_chains_num <= 2)
				break;

			if (window->success_ratio >= IWL_RS_GOOD_RATIO)
				break;

			memcpy(search_tbl, tbl, sz);
			if (rs_toggle_antenna(valid_tx_ant,
					      &search_tbl->current_rate,
					      search_tbl)) {
				update_search_tbl_counter = 1;
				goto out;
			}
			break;
		case IWL_MIMO2_SWITCH_SISO_A:
		case IWL_MIMO2_SWITCH_SISO_B:
		case IWL_MIMO2_SWITCH_SISO_C:
			IWL_DEBUG_RATE(mvm, "LQ: MIMO2 switch to SISO\n");

			/* Set up new search table for SISO */
			memcpy(search_tbl, tbl, sz);

			if (tbl->action == IWL_MIMO2_SWITCH_SISO_A)
				search_tbl->ant_type = ANT_A;
			else if (tbl->action == IWL_MIMO2_SWITCH_SISO_B)
				search_tbl->ant_type = ANT_B;
			else
				search_tbl->ant_type = ANT_C;

			if (!rs_is_valid_ant(valid_tx_ant,
					     search_tbl->ant_type))
				break;

			ret = rs_switch_to_siso(mvm, lq_sta, sta,
						 search_tbl, index);
			if (!ret)
				goto out;

			break;

		case IWL_MIMO2_SWITCH_GI:
			if (!tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				break;
			if (tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				break;

			IWL_DEBUG_RATE(mvm, "LQ: MIMO2 toggle SGI/NGI\n");

			/* Set up new search table for MIMO2 */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = !tbl->is_SGI;
			rs_set_expected_tpt_table(lq_sta, search_tbl);
			/*
			 * If active table already uses the fastest possible
			 * modulation (dual stream with short guard interval),
			 * and it's working well, there's no need to look
			 * for a better type of modulation!
			 */
			if (tbl->is_SGI) {
				s32 tpt = lq_sta->last_tpt / 100;
				if (tpt >= search_tbl->expected_tpt[index])
					break;
			}
			search_tbl->current_rate =
				rate_n_flags_from_tbl(mvm, search_tbl,
						      index, is_green);
			update_search_tbl_counter = 1;
			goto out;

		case IWL_MIMO2_SWITCH_MIMO3_ABC:
			IWL_DEBUG_RATE(mvm, "LQ: MIMO2 switch to MIMO3\n");
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			search_tbl->ant_type = ANT_ABC;

			if (!rs_is_valid_ant(valid_tx_ant,
					     search_tbl->ant_type))
				break;

			ret = rs_switch_to_mimo3(mvm, lq_sta, sta,
						 search_tbl, index);
			if (!ret)
				goto out;

			break;
		}
		tbl->action++;
		if (tbl->action > IWL_MIMO2_SWITCH_MIMO3_ABC)
			tbl->action = IWL_MIMO2_SWITCH_ANTENNA1;

		if (tbl->action == start_action)
			break;
	}
	search_tbl->lq_type = LQ_NONE;
	return 0;
 out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	if (tbl->action > IWL_MIMO2_SWITCH_MIMO3_ABC)
		tbl->action = IWL_MIMO2_SWITCH_ANTENNA1;
	if (update_search_tbl_counter)
		search_tbl->action = tbl->action;

	return 0;
}