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
struct iwl_rx_phy_info {int cfg_phy_cnt; int phy_flags; int channel; int /*<<< orphan*/  system_timestamp; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  rate_n_flags; } ;
struct iwl_rx_packet {int data; } ;
struct iwl_rx_mpdu_res_start {int byte_count; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  ampdu_ref; struct iwl_rx_phy_info last_phy_info; } ;
struct iwl_device_cmd {int dummy; } ;
struct ieee80211_rx_status {int antenna; int rate_idx; int vht_nss; int /*<<< orphan*/  band; int /*<<< orphan*/  flag; int /*<<< orphan*/  ampdu_reference; scalar_t__ mactime; int /*<<< orphan*/  signal; int /*<<< orphan*/  freq; void* device_timestamp; } ;
struct ieee80211_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  rx_status ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_STATS_LIMIT (struct iwl_mvm*,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int RATE_HT_MCS_GF_MSK ; 
 int RATE_HT_MCS_INDEX_MSK ; 
#define  RATE_MCS_CHAN_WIDTH_160 131 
#define  RATE_MCS_CHAN_WIDTH_20 130 
#define  RATE_MCS_CHAN_WIDTH_40 129 
#define  RATE_MCS_CHAN_WIDTH_80 128 
 int RATE_MCS_CHAN_WIDTH_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int RATE_MCS_VHT_MSK ; 
 int RATE_VHT_MCS_NSS_MSK ; 
 int RATE_VHT_MCS_NSS_POS ; 
 int RATE_VHT_MCS_RATE_CODE_MSK ; 
 int /*<<< orphan*/  RX_FLAG_160MHZ ; 
 int /*<<< orphan*/  RX_FLAG_40MHZ ; 
 int /*<<< orphan*/  RX_FLAG_80MHZ ; 
 int /*<<< orphan*/  RX_FLAG_AMPDU_DETAILS ; 
 int /*<<< orphan*/  RX_FLAG_HT ; 
 int /*<<< orphan*/  RX_FLAG_HT_GF ; 
 int /*<<< orphan*/  RX_FLAG_SHORTPRE ; 
 int /*<<< orphan*/  RX_FLAG_SHORT_GI ; 
 int /*<<< orphan*/  RX_FLAG_VHT ; 
 int RX_MPDU_RES_STATUS_CRC_OK ; 
 int RX_MPDU_RES_STATUS_OVERRUN_OK ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_AGG ; 
 int RX_RES_PHY_FLAGS_ANTENNA ; 
 int RX_RES_PHY_FLAGS_ANTENNA_POS ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_BAND_24 ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_SHORT_PREAMBLE ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_calc_rssi (struct iwl_mvm*,struct iwl_rx_phy_info*) ; 
 int iwl_mvm_legacy_rate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_pass_packet_to_mac80211 (struct iwl_mvm*,struct ieee80211_hdr*,int,int,struct iwl_rx_cmd_buffer*,struct ieee80211_rx_status*) ; 
 scalar_t__ iwl_mvm_set_mac80211_rx_flag (struct iwl_mvm*,struct ieee80211_hdr*,struct ieee80211_rx_status*,int) ; 
 int le16_to_cpu (int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 scalar_t__ unlikely (int) ; 

int iwl_mvm_rx_rx_mpdu(struct iwl_mvm *mvm, struct iwl_rx_cmd_buffer *rxb,
		       struct iwl_device_cmd *cmd)
{
	struct ieee80211_hdr *hdr;
	struct ieee80211_rx_status rx_status = {};
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_rx_phy_info *phy_info;
	struct iwl_rx_mpdu_res_start *rx_res;
	u32 len;
	u32 ampdu_status;
	u32 rate_n_flags;
	u32 rx_pkt_status;

	phy_info = &mvm->last_phy_info;
	rx_res = (struct iwl_rx_mpdu_res_start *)pkt->data;
	hdr = (struct ieee80211_hdr *)(pkt->data + sizeof(*rx_res));
	len = le16_to_cpu(rx_res->byte_count);
	rx_pkt_status = le32_to_cpup((__le32 *)
		(pkt->data + sizeof(*rx_res) + len));

	memset(&rx_status, 0, sizeof(rx_status));

	/*
	 * drop the packet if it has failed being decrypted by HW
	 */
	if (iwl_mvm_set_mac80211_rx_flag(mvm, hdr, &rx_status, rx_pkt_status)) {
		IWL_DEBUG_DROP(mvm, "Bad decryption results 0x%08x\n",
			       rx_pkt_status);
		return 0;
	}

	if ((unlikely(phy_info->cfg_phy_cnt > 20))) {
		IWL_DEBUG_DROP(mvm, "dsp size out of range [0,20]: %d\n",
			       phy_info->cfg_phy_cnt);
		return 0;
	}

	if (!(rx_pkt_status & RX_MPDU_RES_STATUS_CRC_OK) ||
	    !(rx_pkt_status & RX_MPDU_RES_STATUS_OVERRUN_OK)) {
		IWL_DEBUG_RX(mvm, "Bad CRC or FIFO: 0x%08X.\n", rx_pkt_status);
		return 0;
	}

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_info->rate_n_flags);

	/* rx_status carries information about the packet to mac80211 */
	rx_status.mactime = le64_to_cpu(phy_info->timestamp);
	rx_status.device_timestamp = le32_to_cpu(phy_info->system_timestamp);
	rx_status.band =
		(phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_BAND_24)) ?
				IEEE80211_BAND_2GHZ : IEEE80211_BAND_5GHZ;
	rx_status.freq =
		ieee80211_channel_to_frequency(le16_to_cpu(phy_info->channel),
					       rx_status.band);
	/*
	 * TSF as indicated by the fw is at INA time, but mac80211 expects the
	 * TSF at the beginning of the MPDU.
	 */
	/*rx_status.flag |= RX_FLAG_MACTIME_MPDU;*/

	/* Find max signal strength (dBm) among 3 antenna/receiver chains */
	rx_status.signal = iwl_mvm_calc_rssi(mvm, phy_info);

	IWL_DEBUG_STATS_LIMIT(mvm, "Rssi %d, TSF %llu\n", rx_status.signal,
			      (unsigned long long)rx_status.mactime);

	/*
	 * "antenna number"
	 *
	 * It seems that the antenna field in the phy flags value
	 * is actually a bit field. This is undefined by radiotap,
	 * it wants an actual antenna number but I always get "7"
	 * for most legacy frames I receive indicating that the
	 * same frame was received on all three RX chains.
	 *
	 * I think this field should be removed in favor of a
	 * new 802.11n radiotap field "RX chains" that is defined
	 * as a bitmask.
	 */
	rx_status.antenna = (le16_to_cpu(phy_info->phy_flags) &
				RX_RES_PHY_FLAGS_ANTENNA)
				>> RX_RES_PHY_FLAGS_ANTENNA_POS;

	/* set the preamble flag if appropriate */
	if (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_SHORT_PREAMBLE))
		rx_status.flag |= RX_FLAG_SHORTPRE;

	if (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_AGG)) {
		/*
		 * We know which subframes of an A-MPDU belong
		 * together since we get a single PHY response
		 * from the firmware for all of them
		 */
		rx_status.flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status.ampdu_reference = mvm->ampdu_ref;
	}

	/* Set up the HT phy flags */
	switch (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) {
	case RATE_MCS_CHAN_WIDTH_20:
		break;
	case RATE_MCS_CHAN_WIDTH_40:
		rx_status.flag |= RX_FLAG_40MHZ;
		break;
	case RATE_MCS_CHAN_WIDTH_80:
		rx_status.flag |= RX_FLAG_80MHZ;
		break;
	case RATE_MCS_CHAN_WIDTH_160:
		rx_status.flag |= RX_FLAG_160MHZ;
		break;
	}
	if (rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status.flag |= RX_FLAG_SHORT_GI;
	if (rate_n_flags & RATE_HT_MCS_GF_MSK)
		rx_status.flag |= RX_FLAG_HT_GF;
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		rx_status.flag |= RX_FLAG_HT;
		rx_status.rate_idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
	} else if (rate_n_flags & RATE_MCS_VHT_MSK) {
		rx_status.vht_nss =
			((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
						RATE_VHT_MCS_NSS_POS) + 1;
		rx_status.rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		rx_status.flag |= RX_FLAG_VHT;
	} else {
		rx_status.rate_idx =
			iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							    rx_status.band);
	}

	iwl_mvm_pass_packet_to_mac80211(mvm, hdr, len, ampdu_status,
					rxb, &rx_status);
	return 0;
}