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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct il_scale_tbl_info {int /*<<< orphan*/  lq_type; int /*<<< orphan*/  max_search; scalar_t__ is_SGI; scalar_t__ is_ht40; int /*<<< orphan*/  ant_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  valid_tx_ant; } ;
struct il_priv {TYPE_1__ hw_params; } ;
struct il_lq_sta {size_t is_green; scalar_t__ band; int supp_rates; struct il_priv* drv; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int IL_FIRST_OFDM_RATE ; 
 int /*<<< orphan*/  IL_MAX_SEARCH ; 
 int /*<<< orphan*/  LQ_A ; 
 int /*<<< orphan*/  LQ_G ; 
 int RATE_INVALID ; 
 int /*<<< orphan*/  il4965_first_antenna (int /*<<< orphan*/ ) ; 
 int il4965_num_of_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rate_n_flags_from_tbl (struct il_priv*,struct il_scale_tbl_info*,int,size_t) ; 
 int il4965_rs_get_adjacent_rate (struct il_priv*,size_t,int,int /*<<< orphan*/ ) ; 
 int il4965_rs_get_supported_rates (struct il_lq_sta*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_legacy (int /*<<< orphan*/ ) ; 
 size_t* rs_ht_to_legacy ; 

__attribute__((used)) static u32
il4965_rs_get_lower_rate(struct il_lq_sta *lq_sta,
			 struct il_scale_tbl_info *tbl, u8 scale_idx,
			 u8 ht_possible)
{
	s32 low;
	u16 rate_mask;
	u16 high_low;
	u8 switch_to_legacy = 0;
	u8 is_green = lq_sta->is_green;
	struct il_priv *il = lq_sta->drv;

	/* check if we need to switch from HT to legacy rates.
	 * assumption is that mandatory rates (1Mbps or 6Mbps)
	 * are always supported (spec demand) */
	if (!is_legacy(tbl->lq_type) && (!ht_possible || !scale_idx)) {
		switch_to_legacy = 1;
		scale_idx = rs_ht_to_legacy[scale_idx];
		if (lq_sta->band == IEEE80211_BAND_5GHZ)
			tbl->lq_type = LQ_A;
		else
			tbl->lq_type = LQ_G;

		if (il4965_num_of_ant(tbl->ant_type) > 1)
			tbl->ant_type =
			    il4965_first_antenna(il->hw_params.valid_tx_ant);

		tbl->is_ht40 = 0;
		tbl->is_SGI = 0;
		tbl->max_search = IL_MAX_SEARCH;
	}

	rate_mask = il4965_rs_get_supported_rates(lq_sta, NULL, tbl->lq_type);

	/* Mask with station rate restriction */
	if (is_legacy(tbl->lq_type)) {
		/* supp_rates has no CCK bits in A mode */
		if (lq_sta->band == IEEE80211_BAND_5GHZ)
			rate_mask =
			    (u16) (rate_mask &
				   (lq_sta->supp_rates << IL_FIRST_OFDM_RATE));
		else
			rate_mask = (u16) (rate_mask & lq_sta->supp_rates);
	}

	/* If we switched from HT to legacy, check current rate */
	if (switch_to_legacy && (rate_mask & (1 << scale_idx))) {
		low = scale_idx;
		goto out;
	}

	high_low =
	    il4965_rs_get_adjacent_rate(lq_sta->drv, scale_idx, rate_mask,
					tbl->lq_type);
	low = high_low & 0xff;

	if (low == RATE_INVALID)
		low = scale_idx;

out:
	return il4965_rate_n_flags_from_tbl(lq_sta->drv, tbl, low, is_green);
}