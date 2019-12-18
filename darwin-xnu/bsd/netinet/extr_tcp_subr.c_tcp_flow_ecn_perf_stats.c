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
struct ifnet_stats_per_flow {int srtt; int rttupdated; int rttvar; scalar_t__ connreset; scalar_t__ sack_recovery_episodes; scalar_t__ dsack_recvd; scalar_t__ dsack_sent; scalar_t__ pawsdrop; scalar_t__ reordered_pkts; scalar_t__ rcvoopack; scalar_t__ rxmitpkts; scalar_t__ rxpackets; scalar_t__ txpackets; } ;
struct if_tcp_ecn_perf_stat {int rtt_avg; int rtt_var; int /*<<< orphan*/  rst_drop; int /*<<< orphan*/  sack_episodes; int /*<<< orphan*/  total_reorderpkts; int /*<<< orphan*/  total_oopkts; int /*<<< orphan*/  total_rxmitpkts; int /*<<< orphan*/  total_rxpkts; int /*<<< orphan*/  total_txpkts; } ;

/* Variables and functions */
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 

__attribute__((used)) static inline void
tcp_flow_ecn_perf_stats(struct ifnet_stats_per_flow *ifs,
    struct if_tcp_ecn_perf_stat *stat)
{
	u_int64_t curval, oldval;
	stat->total_txpkts += ifs->txpackets;
	stat->total_rxpkts += ifs->rxpackets;
	stat->total_rxmitpkts += ifs->rxmitpkts;
	stat->total_oopkts += ifs->rcvoopack;
	stat->total_reorderpkts += (ifs->reordered_pkts +
	    ifs->pawsdrop + ifs->dsack_sent + ifs->dsack_recvd);

	/* Average RTT */
	curval = ifs->srtt >> TCP_RTT_SHIFT;
	if (curval > 0 && ifs->rttupdated >= 16) {
		if (stat->rtt_avg == 0) {
			stat->rtt_avg = curval;
		} else {
			oldval = stat->rtt_avg;
			stat->rtt_avg = ((oldval << 4) - oldval + curval) >> 4;
		}
	}

	/* RTT variance */
	curval = ifs->rttvar >> TCP_RTTVAR_SHIFT;
	if (curval > 0 && ifs->rttupdated >= 16) {
		if (stat->rtt_var == 0) {
			stat->rtt_var = curval;
		} else {
			oldval = stat->rtt_var;
			stat->rtt_var =
			    ((oldval << 4) - oldval + curval) >> 4;
		}
	}

	/* SACK episodes */
	stat->sack_episodes += ifs->sack_recovery_episodes;
	if (ifs->connreset)
		stat->rst_drop++;
}