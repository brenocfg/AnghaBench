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
typedef  scalar_t__ u64 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_5__ {TYPE_1__* txstats; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;
struct ath_softc {TYPE_3__ debug; } ;
struct TYPE_4__ {scalar_t__ tx_bytes_all; scalar_t__ tx_pkts_all; } ;

/* Variables and functions */
 size_t ATH9K_PHYERR_CCK_TIMING ; 
 size_t ATH9K_PHYERR_OFDM_TIMING ; 
 size_t ATH9K_PHYERR_RADAR ; 
 int ATH9K_SSTATS_LEN ; 
 int /*<<< orphan*/  AWDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWDATA_RX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 int /*<<< orphan*/  IEEE80211_AC_BK ; 
 int /*<<< orphan*/  IEEE80211_AC_VI ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 size_t PR_QNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  a_aggr ; 
 int /*<<< orphan*/  a_completed ; 
 int /*<<< orphan*/  a_queued_hw ; 
 int /*<<< orphan*/  a_queued_sw ; 
 int /*<<< orphan*/  a_retries ; 
 int /*<<< orphan*/  a_xretries ; 
 int /*<<< orphan*/  completed ; 
 int /*<<< orphan*/  crc_err ; 
 int /*<<< orphan*/  data_underrun ; 
 int /*<<< orphan*/  decrypt_busy_err ; 
 int /*<<< orphan*/  decrypt_crc_err ; 
 int /*<<< orphan*/  delim_underrun ; 
 int /*<<< orphan*/  desc_cfg_err ; 
 int /*<<< orphan*/  fifo_underrun ; 
 int /*<<< orphan*/  mic_err ; 
 int /*<<< orphan*/  phy_err ; 
 int /*<<< orphan*/ * phy_err_stats ; 
 int /*<<< orphan*/  post_delim_crc_err ; 
 int /*<<< orphan*/  pre_delim_crc_err ; 
 int /*<<< orphan*/  queued ; 
 int /*<<< orphan*/  rx_bytes_all ; 
 int /*<<< orphan*/  rx_pkts_all ; 
 int /*<<< orphan*/  timer_exp ; 
 int /*<<< orphan*/  tx_bytes_all ; 
 int /*<<< orphan*/  tx_pkts_all ; 
 int /*<<< orphan*/  xretries ; 
 int /*<<< orphan*/  xtxop ; 

void ath9k_get_et_stats(struct ieee80211_hw *hw,
			struct ieee80211_vif *vif,
			struct ethtool_stats *stats, u64 *data)
{
	struct ath_softc *sc = hw->priv;
	int i = 0;

	data[i++] = (sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BE)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BK)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VI)].tx_pkts_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VO)].tx_pkts_all);
	data[i++] = (sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BE)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_BK)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VI)].tx_bytes_all +
		     sc->debug.stats.txstats[PR_QNUM(IEEE80211_AC_VO)].tx_bytes_all);
	AWDATA_RX(rx_pkts_all);
	AWDATA_RX(rx_bytes_all);

	AWDATA(tx_pkts_all);
	AWDATA(tx_bytes_all);
	AWDATA(queued);
	AWDATA(completed);
	AWDATA(xretries);
	AWDATA(a_aggr);
	AWDATA(a_queued_hw);
	AWDATA(a_queued_sw);
	AWDATA(a_completed);
	AWDATA(a_retries);
	AWDATA(a_xretries);
	AWDATA(fifo_underrun);
	AWDATA(xtxop);
	AWDATA(timer_exp);
	AWDATA(desc_cfg_err);
	AWDATA(data_underrun);
	AWDATA(delim_underrun);

	AWDATA_RX(crc_err);
	AWDATA_RX(decrypt_crc_err);
	AWDATA_RX(phy_err);
	AWDATA_RX(mic_err);
	AWDATA_RX(pre_delim_crc_err);
	AWDATA_RX(post_delim_crc_err);
	AWDATA_RX(decrypt_busy_err);

	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_RADAR]);
	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_OFDM_TIMING]);
	AWDATA_RX(phy_err_stats[ATH9K_PHYERR_CCK_TIMING]);

	WARN_ON(i != ATH9K_SSTATS_LEN);
}