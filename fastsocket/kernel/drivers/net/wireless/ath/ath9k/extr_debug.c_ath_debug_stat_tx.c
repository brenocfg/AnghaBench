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
struct ath_txq {int axq_qnum; } ;
struct ath_tx_status {int ts_status; int ts_flags; int ts_rssi_ctl0; int ts_rssi_ctl1; int ts_rssi_ctl2; int ts_rssi_ext0; int ts_rssi_ext1; int ts_rssi_ext2; int ts_rateindex; int ts_shortretry; int ts_longretry; int ts_rssi; int tid; int qid; int ba_low; int ba_high; } ;
struct TYPE_6__ {TYPE_1__* txstats; } ;
struct TYPE_8__ {int tsidx; int /*<<< orphan*/  samp_lock; TYPE_2__ stats; } ;
struct ath_softc {TYPE_4__ debug; } ;
struct ath_buf {TYPE_3__* bf_mpdu; } ;
struct TYPE_7__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_bytes_all; } ;
typedef  int TX_SAMP_DBG ;

/* Variables and functions */
 int ATH9K_TXERR_FIFO ; 
 int ATH9K_TXERR_FILT ; 
 int ATH9K_TXERR_MASK ; 
 int ATH9K_TXERR_TIMER_EXPIRED ; 
 int ATH9K_TXERR_XRETRY ; 
 int ATH9K_TXERR_XTXOP ; 
 int ATH9K_TX_BA ; 
 int ATH9K_TX_DATA_UNDERRUN ; 
 int ATH9K_TX_DELIM_UNDERRUN ; 
 int ATH9K_TX_DESC_CFG_ERR ; 
 int ATH_DBG_MAX_SAMPLES ; 
 unsigned int ATH_TX_ERROR ; 
 int /*<<< orphan*/  TX_STAT_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a_completed ; 
 int /*<<< orphan*/  a_xretries ; 
 scalar_t__ bf_isampdu (struct ath_buf*) ; 
 int /*<<< orphan*/  completed ; 
 int /*<<< orphan*/  data_underrun ; 
 int /*<<< orphan*/  delim_underrun ; 
 int /*<<< orphan*/  desc_cfg_err ; 
 int /*<<< orphan*/  fifo_underrun ; 
 int jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_exp ; 
 int /*<<< orphan*/  tx_pkts_all ; 
 int /*<<< orphan*/  txerr_filtered ; 
 int /*<<< orphan*/  xretries ; 
 int /*<<< orphan*/  xtxop ; 

void ath_debug_stat_tx(struct ath_softc *sc, struct ath_buf *bf,
		       struct ath_tx_status *ts, struct ath_txq *txq,
		       unsigned int flags)
{
#define TX_SAMP_DBG(c) (sc->debug.bb_mac_samp[sc->debug.sampidx].ts\
			[sc->debug.tsidx].c)
	int qnum = txq->axq_qnum;

	TX_STAT_INC(qnum, tx_pkts_all);
	sc->debug.stats.txstats[qnum].tx_bytes_all += bf->bf_mpdu->len;

	if (bf_isampdu(bf)) {
		if (flags & ATH_TX_ERROR)
			TX_STAT_INC(qnum, a_xretries);
		else
			TX_STAT_INC(qnum, a_completed);
	} else {
		if (ts->ts_status & ATH9K_TXERR_XRETRY)
			TX_STAT_INC(qnum, xretries);
		else
			TX_STAT_INC(qnum, completed);
	}

	if (ts->ts_status & ATH9K_TXERR_FILT)
		TX_STAT_INC(qnum, txerr_filtered);
	if (ts->ts_status & ATH9K_TXERR_FIFO)
		TX_STAT_INC(qnum, fifo_underrun);
	if (ts->ts_status & ATH9K_TXERR_XTXOP)
		TX_STAT_INC(qnum, xtxop);
	if (ts->ts_status & ATH9K_TXERR_TIMER_EXPIRED)
		TX_STAT_INC(qnum, timer_exp);
	if (ts->ts_flags & ATH9K_TX_DESC_CFG_ERR)
		TX_STAT_INC(qnum, desc_cfg_err);
	if (ts->ts_flags & ATH9K_TX_DATA_UNDERRUN)
		TX_STAT_INC(qnum, data_underrun);
	if (ts->ts_flags & ATH9K_TX_DELIM_UNDERRUN)
		TX_STAT_INC(qnum, delim_underrun);

#ifdef CONFIG_ATH9K_MAC_DEBUG
	spin_lock(&sc->debug.samp_lock);
	TX_SAMP_DBG(jiffies) = jiffies;
	TX_SAMP_DBG(rssi_ctl0) = ts->ts_rssi_ctl0;
	TX_SAMP_DBG(rssi_ctl1) = ts->ts_rssi_ctl1;
	TX_SAMP_DBG(rssi_ctl2) = ts->ts_rssi_ctl2;
	TX_SAMP_DBG(rssi_ext0) = ts->ts_rssi_ext0;
	TX_SAMP_DBG(rssi_ext1) = ts->ts_rssi_ext1;
	TX_SAMP_DBG(rssi_ext2) = ts->ts_rssi_ext2;
	TX_SAMP_DBG(rateindex) = ts->ts_rateindex;
	TX_SAMP_DBG(isok) = !!(ts->ts_status & ATH9K_TXERR_MASK);
	TX_SAMP_DBG(rts_fail_cnt) = ts->ts_shortretry;
	TX_SAMP_DBG(data_fail_cnt) = ts->ts_longretry;
	TX_SAMP_DBG(rssi) = ts->ts_rssi;
	TX_SAMP_DBG(tid) = ts->tid;
	TX_SAMP_DBG(qid) = ts->qid;

	if (ts->ts_flags & ATH9K_TX_BA) {
		TX_SAMP_DBG(ba_low) = ts->ba_low;
		TX_SAMP_DBG(ba_high) = ts->ba_high;
	} else {
		TX_SAMP_DBG(ba_low) = 0;
		TX_SAMP_DBG(ba_high) = 0;
	}

	sc->debug.tsidx = (sc->debug.tsidx + 1) % ATH_DBG_MAX_SAMPLES;
	spin_unlock(&sc->debug.samp_lock);
#endif

#undef TX_SAMP_DBG
}