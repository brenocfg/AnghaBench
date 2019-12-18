#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iwl_tx_cmd {int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  tx_flags; scalar_t__ initial_rate_index; int /*<<< orphan*/  data_retry_limit; int /*<<< orphan*/  rts_retry_limit; } ;
struct iwl_mvm {int /*<<< orphan*/  mgmt_last_antenna_idx; int /*<<< orphan*/  fw; TYPE_3__* nvm_data; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {size_t band; TYPE_2__ control; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {int /*<<< orphan*/ * bands; } ;
struct TYPE_4__ {int flags; int idx; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 size_t IEEE80211_BAND_5GHZ ; 
 int IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IWL_BAR_DFAULT_RETRY_LIMIT ; 
 int /*<<< orphan*/  IWL_DEFAULT_TX_RETRY ; 
 int IWL_FIRST_CCK_RATE ; 
 scalar_t__ IWL_FIRST_OFDM_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int /*<<< orphan*/  IWL_MGMT_DFAULT_RETRY_LIMIT ; 
 int IWL_RATE_COUNT_LEGACY ; 
 int /*<<< orphan*/  IWL_RTS_DFAULT_RETRY_LIMIT ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int TX_CMD_FLG_ACK ; 
 int TX_CMD_FLG_BAR ; 
 int TX_CMD_FLG_STA_RATE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_mac80211_idx_to_hwrate (int) ; 
 int /*<<< orphan*/  iwl_mvm_next_antenna (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rate_lowest_index (int /*<<< orphan*/ *,struct ieee80211_sta*) ; 

__attribute__((used)) static void iwl_mvm_set_tx_cmd_rate(struct iwl_mvm *mvm,
				    struct iwl_tx_cmd *tx_cmd,
				    struct ieee80211_tx_info *info,
				    struct ieee80211_sta *sta,
				    __le16 fc)
{
	u32 rate_flags;
	int rate_idx;
	u8 rate_plcp;

	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = IWL_RTS_DFAULT_RETRY_LIMIT;

	/* Set retry limit on DATA packets and Probe Responses*/
	if (ieee80211_is_probe_resp(fc)) {
		tx_cmd->data_retry_limit = IWL_MGMT_DFAULT_RETRY_LIMIT;
		tx_cmd->rts_retry_limit =
			min(tx_cmd->data_retry_limit, tx_cmd->rts_retry_limit);
	} else if (ieee80211_is_back_req(fc)) {
		tx_cmd->data_retry_limit = IWL_BAR_DFAULT_RETRY_LIMIT;
	} else {
		tx_cmd->data_retry_limit = IWL_DEFAULT_TX_RETRY;
	}

	/*
	 * for data packets, rate info comes from the table inside he fw. This
	 * table is controlled by LINK_QUALITY commands
	 */

	if (ieee80211_is_data(fc) && sta) {
		tx_cmd->initial_rate_index = 0;
		tx_cmd->tx_flags |= cpu_to_le32(TX_CMD_FLG_STA_RATE);
		return;
	} else if (ieee80211_is_back_req(fc)) {
		tx_cmd->tx_flags |=
			cpu_to_le32(TX_CMD_FLG_ACK | TX_CMD_FLG_BAR);
	}

	/* HT rate doesn't make sense for a non data frame */
	WARN_ONCE(info->control.rates[0].flags & IEEE80211_TX_RC_MCS,
		  "Got an HT rate for a non data frame 0x%x\n",
		  info->control.rates[0].flags);

	rate_idx = info->control.rates[0].idx;
	/* if the rate isn't a well known legacy rate, take the lowest one */
	if (rate_idx < 0 || rate_idx > IWL_RATE_COUNT_LEGACY)
		rate_idx = rate_lowest_index(
				&mvm->nvm_data->bands[info->band], sta);

	/* For 5 GHZ band, remap mac80211 rate indices into driver indices */
	if (info->band == IEEE80211_BAND_5GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;

	/* For 2.4 GHZ band, check that there is no need to remap */
	BUILD_BUG_ON(IWL_FIRST_CCK_RATE != 0);

	/* Get PLCP rate for tx_cmd->rate_n_flags */
	rate_plcp = iwl_mvm_mac80211_idx_to_hwrate(rate_idx);

	mvm->mgmt_last_antenna_idx =
		iwl_mvm_next_antenna(mvm, iwl_fw_valid_tx_ant(mvm->fw),
				     mvm->mgmt_last_antenna_idx);
	rate_flags = BIT(mvm->mgmt_last_antenna_idx) << RATE_MCS_ANT_POS;

	/* Set CCK flag as needed */
	if ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags = cpu_to_le32((u32)rate_plcp | rate_flags);
}