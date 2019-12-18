#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct il_station_priv {int dummy; } ;
struct il_scale_tbl_info {int ant_type; int current_rate; } ;
struct TYPE_5__ {size_t valid_tx_ant; } ;
struct il_priv {TYPE_2__* stations; int /*<<< orphan*/  band; TYPE_1__ hw_params; } ;
struct TYPE_7__ {size_t sta_id; } ;
struct il_lq_sta {int last_txrate_idx; size_t active_tbl; TYPE_3__ lq; struct il_scale_tbl_info* lq_info; int /*<<< orphan*/  search_better_tbl; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_conf {int dummy; } ;
struct TYPE_8__ {int plcp; } ;
struct TYPE_6__ {TYPE_3__* lq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int IL_FIRST_CCK_RATE ; 
 int IL_LAST_CCK_RATE ; 
 int RATE_COUNT ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int il4965_first_antenna (size_t) ; 
 int il4965_rate_n_flags_from_tbl (struct il_priv*,struct il_scale_tbl_info*,int,size_t) ; 
 int /*<<< orphan*/  il4965_rs_fill_link_cmd (int /*<<< orphan*/ *,struct il_lq_sta*,int) ; 
 int /*<<< orphan*/  il4965_rs_get_tbl_info_from_mcs (int,int /*<<< orphan*/ ,struct il_scale_tbl_info*,int*) ; 
 int /*<<< orphan*/  il4965_rs_is_valid_ant (size_t,int) ; 
 int /*<<< orphan*/  il4965_rs_set_expected_tpt_table (struct il_lq_sta*,struct il_scale_tbl_info*) ; 
 int /*<<< orphan*/  il4965_rs_toggle_antenna (size_t,int*,struct il_scale_tbl_info*) ; 
 size_t il4965_rs_use_green (struct il_priv*,struct ieee80211_sta*) ; 
 TYPE_4__* il_rates ; 
 int /*<<< orphan*/  il_send_lq_cmd (struct il_priv*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il4965_rs_initialize_lq(struct il_priv *il, struct ieee80211_conf *conf,
			struct ieee80211_sta *sta, struct il_lq_sta *lq_sta)
{
	struct il_scale_tbl_info *tbl;
	int rate_idx;
	int i;
	u32 rate;
	u8 use_green;
	u8 active_tbl = 0;
	u8 valid_tx_ant;
	struct il_station_priv *sta_priv;

	if (!sta || !lq_sta)
		return;

	use_green = il4965_rs_use_green(il, sta);
	sta_priv = (void *)sta->drv_priv;

	i = lq_sta->last_txrate_idx;

	valid_tx_ant = il->hw_params.valid_tx_ant;

	if (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	else
		active_tbl = 1 - lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	if (i < 0 || i >= RATE_COUNT)
		i = 0;

	rate = il_rates[i].plcp;
	tbl->ant_type = il4965_first_antenna(valid_tx_ant);
	rate |= tbl->ant_type << RATE_MCS_ANT_POS;

	if (i >= IL_FIRST_CCK_RATE && i <= IL_LAST_CCK_RATE)
		rate |= RATE_MCS_CCK_MSK;

	il4965_rs_get_tbl_info_from_mcs(rate, il->band, tbl, &rate_idx);
	if (!il4965_rs_is_valid_ant(valid_tx_ant, tbl->ant_type))
		il4965_rs_toggle_antenna(valid_tx_ant, &rate, tbl);

	rate = il4965_rate_n_flags_from_tbl(il, tbl, rate_idx, use_green);
	tbl->current_rate = rate;
	il4965_rs_set_expected_tpt_table(lq_sta, tbl);
	il4965_rs_fill_link_cmd(NULL, lq_sta, rate);
	il->stations[lq_sta->lq.sta_id].lq = &lq_sta->lq;
	il_send_lq_cmd(il, &lq_sta->lq, CMD_SYNC, true);
}