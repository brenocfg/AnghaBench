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
typedef  int u32 ;
struct TYPE_5__ {int raw; } ;
struct TYPE_4__ {scalar_t__ cmd; } ;
struct il_rx_pkt {TYPE_2__ u; TYPE_1__ hdr; } ;
struct il_rx_phy_res {int cfg_phy_cnt; int byte_count; int rate_n_flags; int phy_flags; int channel; int beacon_time_stamp; int /*<<< orphan*/  timestamp; } ;
struct il_rx_mpdu_res_start {int byte_count; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ampdu_ref; struct il_rx_phy_res last_phy_res; int /*<<< orphan*/  last_phy_res_valid; } ;
struct il_priv {TYPE_3__ _4965; void* ucode_beacon_time; } ;
struct ieee80211_rx_status {int antenna; int /*<<< orphan*/  ampdu_reference; int /*<<< orphan*/  flag; scalar_t__ mactime; int /*<<< orphan*/  signal; int /*<<< orphan*/  band; int /*<<< orphan*/  rate_idx; int /*<<< orphan*/  freq; } ;
struct ieee80211_hdr {int dummy; } ;
typedef  int __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_DROP (char*,int) ; 
 int /*<<< orphan*/  D_RX (char*,void*) ; 
 int /*<<< orphan*/  D_STATS (char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 scalar_t__ N_RX ; 
 int RATE_MCS_HT40_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int /*<<< orphan*/  RX_FLAG_40MHZ ; 
 int /*<<< orphan*/  RX_FLAG_AMPDU_DETAILS ; 
 int /*<<< orphan*/  RX_FLAG_HT ; 
 int /*<<< orphan*/  RX_FLAG_SHORTPRE ; 
 int /*<<< orphan*/  RX_FLAG_SHORT_GI ; 
 int RX_RES_PHY_FLAGS_AGG_MSK ; 
 int RX_RES_PHY_FLAGS_ANTENNA_MSK ; 
 int RX_RES_PHY_FLAGS_ANTENNA_POS ; 
 int RX_RES_PHY_FLAGS_BAND_24_MSK ; 
 int RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK ; 
 int RX_RES_STATUS_NO_CRC32_ERROR ; 
 int RX_RES_STATUS_NO_RXE_OVERFLOW ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_calc_rssi (struct il_priv*,struct il_rx_phy_res*) ; 
 int /*<<< orphan*/  il4965_hwrate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_pass_packet_to_mac80211 (struct il_priv*,struct ieee80211_hdr*,int,int,struct il_rx_buf*,struct ieee80211_rx_status*) ; 
 int il4965_translate_rx_status (struct il_priv*,void*) ; 
 int le16_to_cpu (int) ; 
 void* le32_to_cpu (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
il4965_hdl_rx(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct ieee80211_hdr *header;
	struct ieee80211_rx_status rx_status = {};
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_rx_phy_res *phy_res;
	__le32 rx_pkt_status;
	struct il_rx_mpdu_res_start *amsdu;
	u32 len;
	u32 ampdu_status;
	u32 rate_n_flags;

	/**
	 * N_RX and N_RX_MPDU are handled differently.
	 *	N_RX: physical layer info is in this buffer
	 *	N_RX_MPDU: physical layer info was sent in separate
	 *		command and cached in il->last_phy_res
	 *
	 * Here we set up local variables depending on which command is
	 * received.
	 */
	if (pkt->hdr.cmd == N_RX) {
		phy_res = (struct il_rx_phy_res *)pkt->u.raw;
		header =
		    (struct ieee80211_hdr *)(pkt->u.raw + sizeof(*phy_res) +
					     phy_res->cfg_phy_cnt);

		len = le16_to_cpu(phy_res->byte_count);
		rx_pkt_status =
		    *(__le32 *) (pkt->u.raw + sizeof(*phy_res) +
				 phy_res->cfg_phy_cnt + len);
		ampdu_status = le32_to_cpu(rx_pkt_status);
	} else {
		if (!il->_4965.last_phy_res_valid) {
			IL_ERR("MPDU frame without cached PHY data\n");
			return;
		}
		phy_res = &il->_4965.last_phy_res;
		amsdu = (struct il_rx_mpdu_res_start *)pkt->u.raw;
		header = (struct ieee80211_hdr *)(pkt->u.raw + sizeof(*amsdu));
		len = le16_to_cpu(amsdu->byte_count);
		rx_pkt_status = *(__le32 *) (pkt->u.raw + sizeof(*amsdu) + len);
		ampdu_status =
		    il4965_translate_rx_status(il, le32_to_cpu(rx_pkt_status));
	}

	if ((unlikely(phy_res->cfg_phy_cnt > 20))) {
		D_DROP("dsp size out of range [0,20]: %d/n",
		       phy_res->cfg_phy_cnt);
		return;
	}

	if (!(rx_pkt_status & RX_RES_STATUS_NO_CRC32_ERROR) ||
	    !(rx_pkt_status & RX_RES_STATUS_NO_RXE_OVERFLOW)) {
		D_RX("Bad CRC or FIFO: 0x%08X.\n", le32_to_cpu(rx_pkt_status));
		return;
	}

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_res->rate_n_flags);

	/* rx_status carries information about the packet to mac80211 */
	rx_status.mactime = le64_to_cpu(phy_res->timestamp);
	rx_status.band =
	    (phy_res->
	     phy_flags & RX_RES_PHY_FLAGS_BAND_24_MSK) ? IEEE80211_BAND_2GHZ :
	    IEEE80211_BAND_5GHZ;
	rx_status.freq =
	    ieee80211_channel_to_frequency(le16_to_cpu(phy_res->channel),
					   rx_status.band);
	rx_status.rate_idx =
	    il4965_hwrate_to_mac80211_idx(rate_n_flags, rx_status.band);
	rx_status.flag = 0;

	/* TSF isn't reliable. In order to allow smooth user experience,
	 * this W/A doesn't propagate it to the mac80211 */
	/*rx_status.flag |= RX_FLAG_MACTIME_START; */

	il->ucode_beacon_time = le32_to_cpu(phy_res->beacon_time_stamp);

	/* Find max signal strength (dBm) among 3 antenna/receiver chains */
	rx_status.signal = il4965_calc_rssi(il, phy_res);

	D_STATS("Rssi %d, TSF %llu\n", rx_status.signal,
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
	rx_status.antenna =
	    (le16_to_cpu(phy_res->phy_flags) & RX_RES_PHY_FLAGS_ANTENNA_MSK) >>
	    RX_RES_PHY_FLAGS_ANTENNA_POS;

	/* set the preamble flag if appropriate */
	if (phy_res->phy_flags & RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK)
		rx_status.flag |= RX_FLAG_SHORTPRE;

	/* Set up the HT phy flags */
	if (rate_n_flags & RATE_MCS_HT_MSK)
		rx_status.flag |= RX_FLAG_HT;
	if (rate_n_flags & RATE_MCS_HT40_MSK)
		rx_status.flag |= RX_FLAG_40MHZ;
	if (rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status.flag |= RX_FLAG_SHORT_GI;

	if (phy_res->phy_flags & RX_RES_PHY_FLAGS_AGG_MSK) {
		/* We know which subframes of an A-MPDU belong
		 * together since we get a single PHY response
		 * from the firmware for all of them.
		 */

		rx_status.flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status.ampdu_reference = il->_4965.ampdu_ref;
	}

	il4965_pass_packet_to_mac80211(il, header, len, ampdu_status, rxb,
				       &rx_status);
}