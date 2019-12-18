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
typedef  int u8 ;
typedef  int u32 ;
struct il_tx_cmd {int data_retry_limit; int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  tx_flags; scalar_t__ initial_rate_idx; int /*<<< orphan*/  rts_retry_limit; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid_tx_ant; } ;
struct il_priv {int /*<<< orphan*/  mgmt_tx_ant; TYPE_3__ hw_params; int /*<<< orphan*/ * bands; } ;
struct TYPE_6__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {size_t band; TYPE_2__ control; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_8__ {int plcp; } ;
struct TYPE_5__ {int idx; int flags; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_TX_RC_MCS ; 
 int IL4965_DEFAULT_TX_RETRY ; 
 int IL_FIRST_CCK_RATE ; 
 scalar_t__ IL_FIRST_OFDM_RATE ; 
 int IL_LAST_CCK_RATE ; 
 int RATE_COUNT_LEGACY ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int /*<<< orphan*/  TX_CMD_FLG_STA_RATE_MSK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_toggle_tx_ant (struct il_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* il_rates ; 
 int /*<<< orphan*/  min (int,int const) ; 
 int rate_lowest_index (int /*<<< orphan*/ *,struct ieee80211_sta*) ; 

__attribute__((used)) static void
il4965_tx_cmd_build_rate(struct il_priv *il,
			 struct il_tx_cmd *tx_cmd,
			 struct ieee80211_tx_info *info,
			 struct ieee80211_sta *sta,
			 __le16 fc)
{
	const u8 rts_retry_limit = 60;
	u32 rate_flags;
	int rate_idx;
	u8 data_retry_limit;
	u8 rate_plcp;

	/* Set retry limit on DATA packets and Probe Responses */
	if (ieee80211_is_probe_resp(fc))
		data_retry_limit = 3;
	else
		data_retry_limit = IL4965_DEFAULT_TX_RETRY;
	tx_cmd->data_retry_limit = data_retry_limit;
	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = min(data_retry_limit, rts_retry_limit);

	/* DATA packets will use the uCode station table for rate/antenna
	 * selection */
	if (ieee80211_is_data(fc)) {
		tx_cmd->initial_rate_idx = 0;
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;
		return;
	}

	/**
	 * If the current TX rate stored in mac80211 has the MCS bit set, it's
	 * not really a TX rate.  Thus, we use the lowest supported rate for
	 * this band.  Also use the lowest supported rate if the stored rate
	 * idx is invalid.
	 */
	rate_idx = info->control.rates[0].idx;
	if ((info->control.rates[0].flags & IEEE80211_TX_RC_MCS) || rate_idx < 0
	    || rate_idx > RATE_COUNT_LEGACY)
		rate_idx = rate_lowest_index(&il->bands[info->band], sta);
	/* For 5 GHZ band, remap mac80211 rate indices into driver indices */
	if (info->band == IEEE80211_BAND_5GHZ)
		rate_idx += IL_FIRST_OFDM_RATE;
	/* Get PLCP rate for tx_cmd->rate_n_flags */
	rate_plcp = il_rates[rate_idx].plcp;
	/* Zero out flags for this packet */
	rate_flags = 0;

	/* Set CCK flag as needed */
	if (rate_idx >= IL_FIRST_CCK_RATE && rate_idx <= IL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	/* Set up antennas */
	il4965_toggle_tx_ant(il, &il->mgmt_tx_ant, il->hw_params.valid_tx_ant);
	rate_flags |= BIT(il->mgmt_tx_ant) << RATE_MCS_ANT_POS;

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags = cpu_to_le32(rate_plcp | rate_flags);
}