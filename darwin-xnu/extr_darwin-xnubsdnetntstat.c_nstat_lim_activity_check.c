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
struct if_lim_perf_stat {scalar_t__ lim_total_txpkts; int lim_total_rxpkts; int lim_conn_attempts; int lim_packet_loss_percent; int lim_total_retxpkts; int lim_packet_ooo_percent; int lim_total_oopkts; int lim_conn_timeout_percent; int lim_conn_timeouts; scalar_t__ lim_dl_max_bandwidth; int lim_dl_detected; scalar_t__ lim_ul_max_bandwidth; scalar_t__ lim_rtt_min; int lim_ul_detected; scalar_t__ lim_bk_txpkts; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int NSTAT_LIM_CONN_TIMEOUT_PERCENT_THRESHOLD ; 
 scalar_t__ NSTAT_LIM_DL_MAX_BANDWIDTH_THRESHOLD ; 
 int NSTAT_LIM_PACKET_LOSS_PERCENT_THRESHOLD ; 
 scalar_t__ NSTAT_LIM_UL_MAX_BANDWIDTH_THRESHOLD ; 
 scalar_t__ NSTAT_LIM_UL_MIN_RTT_THRESHOLD ; 
 int /*<<< orphan*/  TRUE ; 
 int nstat_lim_min_rx_pkts ; 
 scalar_t__ nstat_lim_min_tx_pkts ; 

__attribute__((used)) static boolean_t
nstat_lim_activity_check(struct if_lim_perf_stat *st)
{
	/* check that the current activity is enough to report stats */
	if (st->lim_total_txpkts < nstat_lim_min_tx_pkts ||
	    st->lim_total_rxpkts < nstat_lim_min_rx_pkts ||
	    st->lim_conn_attempts == 0)
		return (FALSE);

	/*
	 * Compute percentages if there was enough activity. Use
	 * shift-left by 10 to preserve precision.
	 */
	st->lim_packet_loss_percent = ((st->lim_total_retxpkts << 10) /
	    st->lim_total_txpkts) * 100;

	st->lim_packet_ooo_percent = ((st->lim_total_oopkts << 10) /
	    st->lim_total_rxpkts) * 100;

	st->lim_conn_timeout_percent = ((st->lim_conn_timeouts << 10) /
	    st->lim_conn_attempts) * 100;

	/*
	 * Is Low Internet detected? First order metrics are bandwidth
	 * and RTT. If these metrics are below the minimum thresholds
	 * defined then the network attachment can be classified as
	 * having Low Internet capacity.
	 *
	 * High connection timeout rate also indicates Low Internet
	 * capacity.
	 */
	if (st->lim_dl_max_bandwidth > 0 &&
	    st->lim_dl_max_bandwidth <= NSTAT_LIM_DL_MAX_BANDWIDTH_THRESHOLD)
		st->lim_dl_detected = 1;

	if ((st->lim_ul_max_bandwidth > 0 &&
	    st->lim_ul_max_bandwidth <= NSTAT_LIM_UL_MAX_BANDWIDTH_THRESHOLD) ||
	    st->lim_rtt_min >= NSTAT_LIM_UL_MIN_RTT_THRESHOLD)
		st->lim_ul_detected = 1;

	if (st->lim_conn_attempts > 20 &&
	    st->lim_conn_timeout_percent >=
	    NSTAT_LIM_CONN_TIMEOUT_PERCENT_THRESHOLD)
		st->lim_ul_detected = 1;
	/*
	 * Second order metrics: If there was high packet loss even after
	 * using delay based algorithms then we classify it as Low Internet
	 * again
	 */
	if (st->lim_bk_txpkts >= nstat_lim_min_tx_pkts &&
	    st->lim_packet_loss_percent >=
	    NSTAT_LIM_PACKET_LOSS_PERCENT_THRESHOLD)
		st->lim_ul_detected = 1;
	return (TRUE);
}