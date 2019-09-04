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
struct TYPE_5__ {int /*<<< orphan*/  rxmitpkts; int /*<<< orphan*/  rxoutoforderbytes; int /*<<< orphan*/  txretransmitbytes; } ;
struct tcpcb {int t_flags; TYPE_2__* t_bwmeas; int /*<<< orphan*/  t_rttvar; int /*<<< orphan*/  t_rttupdated; int /*<<< orphan*/  t_srtt; int /*<<< orphan*/  t_dsack_recvd; int /*<<< orphan*/  t_dsack_sent; int /*<<< orphan*/  t_reordered_pkts; int /*<<< orphan*/  t_sack_recovery_episode; int /*<<< orphan*/  t_pawsdrop; int /*<<< orphan*/  t_rcvoopack; TYPE_1__ t_stat; int /*<<< orphan*/  ecn_flags; struct inpcb* t_inpcb; } ;
struct socket {scalar_t__ so_error; TYPE_3__* so_tc_stats; } ;
struct inpcb {int inp_vflag; TYPE_4__* inp_stat; struct socket* inp_socket; } ;
struct ifnet_stats_per_flow {int ipv4; int local; int connreset; int conntimeout; scalar_t__ bw_sndbw_max; scalar_t__ bw_rcvbw_max; int /*<<< orphan*/  rxpackets; int /*<<< orphan*/  txpackets; int /*<<< orphan*/  bk_txpackets; int /*<<< orphan*/  rttmin; int /*<<< orphan*/  rttvar; int /*<<< orphan*/  rttupdated; int /*<<< orphan*/  srtt; int /*<<< orphan*/  dsack_recvd; int /*<<< orphan*/  dsack_sent; int /*<<< orphan*/  reordered_pkts; int /*<<< orphan*/  sack_recovery_episodes; int /*<<< orphan*/  pawsdrop; int /*<<< orphan*/  rcvoopack; int /*<<< orphan*/  rxmitpkts; int /*<<< orphan*/  rxoutoforderbytes; int /*<<< orphan*/  txretransmitbytes; int /*<<< orphan*/  ecn_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  rxpackets; int /*<<< orphan*/  txpackets; } ;
struct TYPE_7__ {int /*<<< orphan*/  txpackets; } ;
struct TYPE_6__ {scalar_t__ bw_sndbw_max; scalar_t__ bw_rcvbw_max; } ;

/* Variables and functions */
 scalar_t__ ECONNRESET ; 
 scalar_t__ ETIMEDOUT ; 
 int INP_IPV6 ; 
 size_t MBUF_TC_BK ; 
 int TF_LOCAL ; 
 int /*<<< orphan*/  bzero (struct ifnet_stats_per_flow*,int) ; 
 int /*<<< orphan*/  get_base_rtt (struct tcpcb*) ; 

__attribute__((used)) static inline void
tcp_create_ifnet_stats_per_flow(struct tcpcb *tp,
    struct ifnet_stats_per_flow *ifs)
{
	struct inpcb *inp;
	struct socket *so;
	if (tp == NULL || ifs == NULL)
		return;

	bzero(ifs, sizeof(*ifs));
	inp = tp->t_inpcb;
	so = inp->inp_socket;

	ifs->ipv4 = (inp->inp_vflag & INP_IPV6) ? 0 : 1;
	ifs->local = (tp->t_flags & TF_LOCAL) ? 1 : 0;
	ifs->connreset = (so->so_error == ECONNRESET) ? 1 : 0;
	ifs->conntimeout = (so->so_error == ETIMEDOUT) ? 1 : 0;
	ifs->ecn_flags = tp->ecn_flags;
	ifs->txretransmitbytes = tp->t_stat.txretransmitbytes;
	ifs->rxoutoforderbytes = tp->t_stat.rxoutoforderbytes;
	ifs->rxmitpkts = tp->t_stat.rxmitpkts;
	ifs->rcvoopack = tp->t_rcvoopack;
	ifs->pawsdrop = tp->t_pawsdrop;
	ifs->sack_recovery_episodes = tp->t_sack_recovery_episode;
	ifs->reordered_pkts = tp->t_reordered_pkts;
	ifs->dsack_sent = tp->t_dsack_sent;
	ifs->dsack_recvd = tp->t_dsack_recvd;
	ifs->srtt = tp->t_srtt;
	ifs->rttupdated = tp->t_rttupdated;
	ifs->rttvar = tp->t_rttvar;
	ifs->rttmin = get_base_rtt(tp);
	if (tp->t_bwmeas != NULL && tp->t_bwmeas->bw_sndbw_max > 0) {
		ifs->bw_sndbw_max = tp->t_bwmeas->bw_sndbw_max;
	} else {
		ifs->bw_sndbw_max = 0;
	}
	if (tp->t_bwmeas!= NULL && tp->t_bwmeas->bw_rcvbw_max > 0) {
		ifs->bw_rcvbw_max = tp->t_bwmeas->bw_rcvbw_max;
	} else {
		ifs->bw_rcvbw_max = 0;
	}
	ifs->bk_txpackets = so->so_tc_stats[MBUF_TC_BK].txpackets;
	ifs->txpackets = inp->inp_stat->txpackets;
	ifs->rxpackets = inp->inp_stat->rxpackets;
}