#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ len; int* data; } ;
struct ieee80211_rx_status {scalar_t__ signal; int /*<<< orphan*/  flag; int /*<<< orphan*/  antenna; int /*<<< orphan*/  freq; int /*<<< orphan*/  band; int /*<<< orphan*/  mactime; } ;
struct TYPE_11__ {TYPE_3__* chan; } ;
struct TYPE_12__ {TYPE_4__ chandef; } ;
struct ieee80211_hw {TYPE_5__ conf; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;
struct ath_htc_rx_status {int /*<<< orphan*/  rs_datalen; } ;
struct ath_common {int /*<<< orphan*/  curbssid; int /*<<< orphan*/  keymap; } ;
struct TYPE_13__ {int rs_status; int rs_keyix; scalar_t__ rs_rssi; int /*<<< orphan*/  rs_antenna; int /*<<< orphan*/  rs_tstamp; int /*<<< orphan*/  rs_moreaggr; int /*<<< orphan*/  rs_flags; int /*<<< orphan*/  rs_rate; } ;
struct ath9k_htc_rxbuf {TYPE_6__ rxstatus; struct sk_buff* skb; } ;
struct TYPE_8__ {int last_rssi; } ;
struct ath9k_htc_priv {TYPE_7__* ah; TYPE_1__ rx; struct ieee80211_hw* hw; } ;
typedef  scalar_t__ s8 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_9__ {scalar_t__ avgbrssi; } ;
struct TYPE_14__ {scalar_t__ opmode; TYPE_2__ stats; } ;
struct TYPE_10__ {int /*<<< orphan*/  center_freq; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 scalar_t__ ATH9K_RSSI_BAD ; 
 int ATH9K_RXERR_CRC ; 
 int ATH9K_RXERR_DECRYPT ; 
 int ATH9K_RXERR_MIC ; 
 int ATH9K_RXERR_PHY ; 
 int ATH9K_RXKEYIX_INVALID ; 
 scalar_t__ ATH_DEFAULT_NOISE_FLOOR ; 
 scalar_t__ ATH_EP_RND (int,int /*<<< orphan*/ ) ; 
 int ATH_RSSI_DUMMY_MARKER ; 
 int /*<<< orphan*/  ATH_RSSI_EP_MULTIPLIER ; 
 int /*<<< orphan*/  ATH_RSSI_LPF (int,scalar_t__) ; 
 scalar_t__ FCS_LEN ; 
 scalar_t__ HTC_RX_FRAME_HEADER_SIZE ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_MACTIME_END ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int /*<<< orphan*/  ath9k_htc_err_stat_rx (struct ath9k_htc_priv*,struct ath_htc_rx_status*) ; 
 struct ath_common* ath9k_hw_common (TYPE_7__*) ; 
 int /*<<< orphan*/  ath9k_process_rate (struct ieee80211_hw*,struct ieee80211_rx_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,scalar_t__,...) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,struct ath_htc_rx_status*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath9k_rx_prepare(struct ath9k_htc_priv *priv,
			     struct ath9k_htc_rxbuf *rxbuf,
			     struct ieee80211_rx_status *rx_status)

{
	struct ieee80211_hdr *hdr;
	struct ieee80211_hw *hw = priv->hw;
	struct sk_buff *skb = rxbuf->skb;
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath_htc_rx_status *rxstatus;
	int hdrlen, padsize;
	int last_rssi = ATH_RSSI_DUMMY_MARKER;
	__le16 fc;

	if (skb->len < HTC_RX_FRAME_HEADER_SIZE) {
		ath_err(common, "Corrupted RX frame, dropping (len: %d)\n",
			skb->len);
		goto rx_next;
	}

	rxstatus = (struct ath_htc_rx_status *)skb->data;

	if (be16_to_cpu(rxstatus->rs_datalen) -
	    (skb->len - HTC_RX_FRAME_HEADER_SIZE) != 0) {
		ath_err(common,
			"Corrupted RX data len, dropping (dlen: %d, skblen: %d)\n",
			rxstatus->rs_datalen, skb->len);
		goto rx_next;
	}

	ath9k_htc_err_stat_rx(priv, rxstatus);

	/* Get the RX status information */
	memcpy(&rxbuf->rxstatus, rxstatus, HTC_RX_FRAME_HEADER_SIZE);
	skb_pull(skb, HTC_RX_FRAME_HEADER_SIZE);

	hdr = (struct ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;
	hdrlen = ieee80211_get_hdrlen_from_skb(skb);

	padsize = hdrlen & 3;
	if (padsize && skb->len >= hdrlen+padsize+FCS_LEN) {
		memmove(skb->data + padsize, skb->data, hdrlen);
		skb_pull(skb, padsize);
	}

	memset(rx_status, 0, sizeof(struct ieee80211_rx_status));

	if (rxbuf->rxstatus.rs_status != 0) {
		if (rxbuf->rxstatus.rs_status & ATH9K_RXERR_CRC)
			rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
		if (rxbuf->rxstatus.rs_status & ATH9K_RXERR_PHY)
			goto rx_next;

		if (rxbuf->rxstatus.rs_status & ATH9K_RXERR_DECRYPT) {
			/* FIXME */
		} else if (rxbuf->rxstatus.rs_status & ATH9K_RXERR_MIC) {
			if (ieee80211_is_ctl(fc))
				/*
				 * Sometimes, we get invalid
				 * MIC failures on valid control frames.
				 * Remove these mic errors.
				 */
				rxbuf->rxstatus.rs_status &= ~ATH9K_RXERR_MIC;
			else
				rx_status->flag |= RX_FLAG_MMIC_ERROR;
		}

		/*
		 * Reject error frames with the exception of
		 * decryption and MIC failures. For monitor mode,
		 * we also ignore the CRC error.
		 */
		if (priv->ah->opmode == NL80211_IFTYPE_MONITOR) {
			if (rxbuf->rxstatus.rs_status &
			    ~(ATH9K_RXERR_DECRYPT | ATH9K_RXERR_MIC |
			      ATH9K_RXERR_CRC))
				goto rx_next;
		} else {
			if (rxbuf->rxstatus.rs_status &
			    ~(ATH9K_RXERR_DECRYPT | ATH9K_RXERR_MIC)) {
				goto rx_next;
			}
		}
	}

	if (!(rxbuf->rxstatus.rs_status & ATH9K_RXERR_DECRYPT)) {
		u8 keyix;
		keyix = rxbuf->rxstatus.rs_keyix;
		if (keyix != ATH9K_RXKEYIX_INVALID) {
			rx_status->flag |= RX_FLAG_DECRYPTED;
		} else if (ieee80211_has_protected(fc) &&
			   skb->len >= hdrlen + 4) {
			keyix = skb->data[hdrlen + 3] >> 6;
			if (test_bit(keyix, common->keymap))
				rx_status->flag |= RX_FLAG_DECRYPTED;
		}
	}

	ath9k_process_rate(hw, rx_status, rxbuf->rxstatus.rs_rate,
			   rxbuf->rxstatus.rs_flags);

	if (rxbuf->rxstatus.rs_rssi != ATH9K_RSSI_BAD &&
	    !rxbuf->rxstatus.rs_moreaggr)
		ATH_RSSI_LPF(priv->rx.last_rssi,
			     rxbuf->rxstatus.rs_rssi);

	last_rssi = priv->rx.last_rssi;

	if (ieee80211_is_beacon(hdr->frame_control) &&
	    !is_zero_ether_addr(common->curbssid) &&
	    ether_addr_equal(hdr->addr3, common->curbssid)) {
		s8 rssi = rxbuf->rxstatus.rs_rssi;

		if (likely(last_rssi != ATH_RSSI_DUMMY_MARKER))
			rssi = ATH_EP_RND(last_rssi, ATH_RSSI_EP_MULTIPLIER);

		if (rssi < 0)
			rssi = 0;

		priv->ah->stats.avgbrssi = rssi;
	}

	rx_status->mactime = be64_to_cpu(rxbuf->rxstatus.rs_tstamp);
	rx_status->band = hw->conf.chandef.chan->band;
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->signal =  rxbuf->rxstatus.rs_rssi + ATH_DEFAULT_NOISE_FLOOR;
	rx_status->antenna = rxbuf->rxstatus.rs_antenna;
	rx_status->flag |= RX_FLAG_MACTIME_END;

	return true;

rx_next:
	return false;
}