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
typedef  int u32 ;
struct iwl_mvm {int /*<<< orphan*/  scan_last_antenna_idx; int /*<<< orphan*/  fw; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int IEEE80211_BAND_2GHZ ; 
 int IWL_RATE_1M_PLCP ; 
 int IWL_RATE_6M_PLCP ; 
 int RATE_MCS_ANT_POS ; 
 int RATE_MCS_CCK_MSK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  iwl_fw_valid_tx_ant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_next_antenna (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le32
iwl_mvm_scan_rate_n_flags(struct iwl_mvm *mvm, enum ieee80211_band band,
			  bool no_cck)
{
	u32 tx_ant;

	mvm->scan_last_antenna_idx =
		iwl_mvm_next_antenna(mvm, iwl_fw_valid_tx_ant(mvm->fw),
				     mvm->scan_last_antenna_idx);
	tx_ant = BIT(mvm->scan_last_antenna_idx) << RATE_MCS_ANT_POS;

	if (band == IEEE80211_BAND_2GHZ && !no_cck)
		return cpu_to_le32(IWL_RATE_1M_PLCP | RATE_MCS_CCK_MSK |
				   tx_ant);
	else
		return cpu_to_le32(IWL_RATE_6M_PLCP | tx_ant);
}