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
typedef  int u_int64_t ;
struct ifnet_stats_per_flow {int bw_sndbw_max; int bw_rcvbw_max; int srtt; int rttupdated; int rttvar; scalar_t__ rttmin; scalar_t__ bk_txpackets; scalar_t__ conntimeout; scalar_t__ rcvoopack; scalar_t__ rxmitpkts; scalar_t__ rxpackets; scalar_t__ txpackets; } ;
struct if_lim_perf_stat {int lim_rtt_average; int lim_rtt_variance; scalar_t__ lim_rtt_min; int /*<<< orphan*/  lim_bk_txpkts; int /*<<< orphan*/  lim_conn_timeouts; int /*<<< orphan*/  lim_conn_attempts; void* lim_dl_max_bandwidth; void* lim_ul_max_bandwidth; int /*<<< orphan*/  lim_total_oopkts; int /*<<< orphan*/  lim_total_retxpkts; int /*<<< orphan*/  lim_total_rxpkts; int /*<<< orphan*/  lim_total_txpkts; } ;

/* Variables and functions */
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 
 void* max (void*,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
tcp_flow_lim_stats(struct ifnet_stats_per_flow *ifs,
    struct if_lim_perf_stat *stat)
{
	u_int64_t curval, oldval;

	stat->lim_total_txpkts += ifs->txpackets;
	stat->lim_total_rxpkts += ifs->rxpackets;
	stat->lim_total_retxpkts += ifs->rxmitpkts;
	stat->lim_total_oopkts += ifs->rcvoopack;

	if (ifs->bw_sndbw_max > 0) {
		/* convert from bytes per ms to bits per second */
		ifs->bw_sndbw_max *= 8000;
		stat->lim_ul_max_bandwidth = max(stat->lim_ul_max_bandwidth,
		    ifs->bw_sndbw_max);
	}

	if (ifs->bw_rcvbw_max > 0) {
		/* convert from bytes per ms to bits per second */
		ifs->bw_rcvbw_max *= 8000;
		stat->lim_dl_max_bandwidth = max(stat->lim_dl_max_bandwidth,
		    ifs->bw_rcvbw_max);
	}

	/* Average RTT */
	curval = ifs->srtt >> TCP_RTT_SHIFT;
	if (curval > 0 && ifs->rttupdated >= 16) {
		if (stat->lim_rtt_average == 0) {
			stat->lim_rtt_average = curval;
		} else {
			oldval = stat->lim_rtt_average;
			stat->lim_rtt_average =
			    ((oldval << 4) - oldval + curval) >> 4;
		}
	}

	/* RTT variance */
	curval = ifs->rttvar >> TCP_RTTVAR_SHIFT;
	if (curval > 0 && ifs->rttupdated >= 16) {
		if (stat->lim_rtt_variance == 0) {
			stat->lim_rtt_variance = curval;
		} else {
			oldval = stat->lim_rtt_variance;
			stat->lim_rtt_variance =
			    ((oldval << 4) - oldval + curval) >> 4;
		}
	}

	if (stat->lim_rtt_min == 0) {
		stat->lim_rtt_min = ifs->rttmin;
	} else {
		stat->lim_rtt_min = min(stat->lim_rtt_min, ifs->rttmin);
	}

	/* connection timeouts */
	stat->lim_conn_attempts++;
	if (ifs->conntimeout)
		stat->lim_conn_timeouts++;

	/* bytes sent using background delay-based algorithms */
	stat->lim_bk_txpkts += ifs->bk_txpackets;

}