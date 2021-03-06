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
struct iwl_scale_tbl_info {int action; int /*<<< orphan*/  lq_type; int /*<<< orphan*/  ant_type; int /*<<< orphan*/  is_SGI; int /*<<< orphan*/  current_rate; struct iwl_rate_scale_data* win; } ;
struct iwl_rate_scale_data {int /*<<< orphan*/  success_ratio; } ;
struct iwl_mvm {int /*<<< orphan*/  fw; } ;
struct iwl_lq_sta {size_t active_tbl; int search_better_tbl; scalar_t__ action_counter; struct iwl_scale_tbl_info* lq_info; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_AB ; 
 int /*<<< orphan*/  ANT_ABC ; 
 int /*<<< orphan*/  ANT_AC ; 
 int /*<<< orphan*/  ANT_BC ; 
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 
#define  IWL_LEGACY_SWITCH_ANTENNA1 134 
#define  IWL_LEGACY_SWITCH_ANTENNA2 133 
#define  IWL_LEGACY_SWITCH_MIMO2_AB 132 
#define  IWL_LEGACY_SWITCH_MIMO2_AC 131 
#define  IWL_LEGACY_SWITCH_MIMO2_BC 130 
#define  IWL_LEGACY_SWITCH_MIMO3_ABC 129 
#define  IWL_LEGACY_SWITCH_SISO 128 
 int IWL_RATE_COUNT ; 
 int /*<<< orphan*/  IWL_RS_GOOD_RATIO ; 
 int /*<<< orphan*/  LQ_NONE ; 
 int iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct iwl_scale_tbl_info*,struct iwl_scale_tbl_info*,int) ; 
 int num_of_ant (int) ; 
 int /*<<< orphan*/  rs_is_valid_ant (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_set_expected_tpt_table (struct iwl_lq_sta*,struct iwl_scale_tbl_info*) ; 
 int rs_switch_to_mimo2 (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int rs_switch_to_mimo3 (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int rs_switch_to_siso (struct iwl_mvm*,struct iwl_lq_sta*,struct ieee80211_sta*,struct iwl_scale_tbl_info*,int) ; 
 int /*<<< orphan*/  rs_toggle_antenna (int,int /*<<< orphan*/ *,struct iwl_scale_tbl_info*) ; 

__attribute__((used)) static int rs_move_legacy_other(struct iwl_mvm *mvm,
				struct iwl_lq_sta *lq_sta,
				struct ieee80211_sta *sta,
				int index)
{
	struct iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	struct iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	struct iwl_rate_scale_data *window = &(tbl->win[index]);
	u32 sz = (sizeof(struct iwl_scale_tbl_info) -
		  (sizeof(struct iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = iwl_fw_valid_tx_ant(mvm->fw);
	u8 tx_chains_num = num_of_ant(valid_tx_ant);
	int ret;
	u8 update_search_tbl_counter = 0;

	start_action = tbl->action;
	while (1) {
		lq_sta->action_counter++;
		switch (tbl->action) {
		case IWL_LEGACY_SWITCH_ANTENNA1:
		case IWL_LEGACY_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(mvm, "LQ: Legacy toggle Antenna\n");

			if ((tbl->action == IWL_LEGACY_SWITCH_ANTENNA1 &&
			     tx_chains_num <= 1) ||
			    (tbl->action == IWL_LEGACY_SWITCH_ANTENNA2 &&
			     tx_chains_num <= 2))
				break;

			/* Don't change antenna if success has been great */
			if (window->success_ratio >= IWL_RS_GOOD_RATIO)
				break;

			/* Set up search table to try other antenna */
			memcpy(search_tbl, tbl, sz);

			if (rs_toggle_antenna(valid_tx_ant,
					      &search_tbl->current_rate,
					      search_tbl)) {
				update_search_tbl_counter = 1;
				rs_set_expected_tpt_table(lq_sta, search_tbl);
				goto out;
			}
			break;
		case IWL_LEGACY_SWITCH_SISO:
			IWL_DEBUG_RATE(mvm, "LQ: Legacy switch to SISO\n");

			/* Set up search table to try SISO */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			ret = rs_switch_to_siso(mvm, lq_sta, sta,
						 search_tbl, index);
			if (!ret) {
				lq_sta->action_counter = 0;
				goto out;
			}

			break;
		case IWL_LEGACY_SWITCH_MIMO2_AB:
		case IWL_LEGACY_SWITCH_MIMO2_AC:
		case IWL_LEGACY_SWITCH_MIMO2_BC:
			IWL_DEBUG_RATE(mvm, "LQ: Legacy switch to MIMO2\n");

			/* Set up search table to try MIMO */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			if (tbl->action == IWL_LEGACY_SWITCH_MIMO2_AB)
				search_tbl->ant_type = ANT_AB;
			else if (tbl->action == IWL_LEGACY_SWITCH_MIMO2_AC)
				search_tbl->ant_type = ANT_AC;
			else
				search_tbl->ant_type = ANT_BC;

			if (!rs_is_valid_ant(valid_tx_ant,
					     search_tbl->ant_type))
				break;

			ret = rs_switch_to_mimo2(mvm, lq_sta, sta,
						 search_tbl, index);
			if (!ret) {
				lq_sta->action_counter = 0;
				goto out;
			}
			break;

		case IWL_LEGACY_SWITCH_MIMO3_ABC:
			IWL_DEBUG_RATE(mvm, "LQ: Legacy switch to MIMO3\n");

			/* Set up search table to try MIMO3 */
			memcpy(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			search_tbl->ant_type = ANT_ABC;

			if (!rs_is_valid_ant(valid_tx_ant,
					     search_tbl->ant_type))
				break;

			ret = rs_switch_to_mimo3(mvm, lq_sta, sta,
						 search_tbl, index);
			if (!ret) {
				lq_sta->action_counter = 0;
				goto out;
			}
			break;
		}
		tbl->action++;
		if (tbl->action > IWL_LEGACY_SWITCH_MIMO3_ABC)
			tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;

		if (tbl->action == start_action)
			break;
	}
	search_tbl->lq_type = LQ_NONE;
	return 0;

out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	if (tbl->action > IWL_LEGACY_SWITCH_MIMO3_ABC)
		tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;
	if (update_search_tbl_counter)
		search_tbl->action = tbl->action;
	return 0;
}