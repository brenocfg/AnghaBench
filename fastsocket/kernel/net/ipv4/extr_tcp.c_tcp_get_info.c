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
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int /*<<< orphan*/  space; } ;
struct TYPE_7__ {int /*<<< orphan*/  rtt; } ;
struct TYPE_5__ {int /*<<< orphan*/  rcv_wscale; int /*<<< orphan*/  snd_wscale; scalar_t__ wscale_ok; scalar_t__ tstamp_ok; } ;
struct tcp_sock {int ecn_flags; int /*<<< orphan*/  total_retrans; TYPE_4__ rcvq_space; TYPE_3__ rcv_rtt_est; int /*<<< orphan*/  reordering; int /*<<< orphan*/  advmss; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  mdev; int /*<<< orphan*/  srtt; int /*<<< orphan*/  rcv_ssthresh; scalar_t__ rcv_tstamp; scalar_t__ lsndtime; int /*<<< orphan*/  fackets_out; int /*<<< orphan*/  retrans_out; int /*<<< orphan*/  lost_out; int /*<<< orphan*/  sacked_out; int /*<<< orphan*/  packets_out; int /*<<< orphan*/  mss_cache; TYPE_1__ rx_opt; } ;
struct tcp_info {scalar_t__ tcpi_state; int tcpi_rto; int tcpi_ato; int tcpi_rtt; int tcpi_rttvar; int tcpi_rcv_rtt; int /*<<< orphan*/  tcpi_total_retrans; int /*<<< orphan*/  tcpi_rcv_space; int /*<<< orphan*/  tcpi_reordering; int /*<<< orphan*/  tcpi_advmss; int /*<<< orphan*/  tcpi_snd_cwnd; int /*<<< orphan*/  tcpi_snd_ssthresh; int /*<<< orphan*/  tcpi_rcv_ssthresh; int /*<<< orphan*/  tcpi_pmtu; void* tcpi_last_ack_recv; void* tcpi_last_data_recv; void* tcpi_last_data_sent; int /*<<< orphan*/  tcpi_fackets; int /*<<< orphan*/  tcpi_retrans; int /*<<< orphan*/  tcpi_lost; int /*<<< orphan*/  tcpi_sacked; int /*<<< orphan*/  tcpi_unacked; int /*<<< orphan*/  tcpi_rcv_mss; int /*<<< orphan*/  tcpi_snd_mss; int /*<<< orphan*/  tcpi_options; int /*<<< orphan*/  tcpi_rcv_wscale; int /*<<< orphan*/  tcpi_snd_wscale; int /*<<< orphan*/  tcpi_backoff; int /*<<< orphan*/  tcpi_probes; int /*<<< orphan*/  tcpi_retransmits; int /*<<< orphan*/  tcpi_ca_state; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_max_ack_backlog; int /*<<< orphan*/  sk_ack_backlog; } ;
struct TYPE_6__ {scalar_t__ lrcvtime; int /*<<< orphan*/  rcv_mss; int /*<<< orphan*/  ato; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_pmtu_cookie; TYPE_2__ icsk_ack; int /*<<< orphan*/  icsk_rto; int /*<<< orphan*/  icsk_backoff; int /*<<< orphan*/  icsk_probes_out; int /*<<< orphan*/  icsk_retransmits; int /*<<< orphan*/  icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPI_OPT_ECN ; 
 int /*<<< orphan*/  TCPI_OPT_SACK ; 
 int /*<<< orphan*/  TCPI_OPT_TIMESTAMPS ; 
 int /*<<< orphan*/  TCPI_OPT_WSCALE ; 
 int TCP_ECN_OK ; 
 scalar_t__ TCP_LISTEN ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 void* jiffies_to_msecs (scalar_t__) ; 
 int jiffies_to_usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tcp_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcp_is_sack (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_time_stamp ; 

void tcp_get_info(struct sock *sk, struct tcp_info *info)
{
	struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_connection_sock *icsk = inet_csk(sk);
	u32 now = tcp_time_stamp;

	memset(info, 0, sizeof(*info));

	info->tcpi_state = sk->sk_state;
	info->tcpi_ca_state = icsk->icsk_ca_state;
	info->tcpi_retransmits = icsk->icsk_retransmits;
	info->tcpi_probes = icsk->icsk_probes_out;
	info->tcpi_backoff = icsk->icsk_backoff;

	if (tp->rx_opt.tstamp_ok)
		info->tcpi_options |= TCPI_OPT_TIMESTAMPS;
	if (tcp_is_sack(tp))
		info->tcpi_options |= TCPI_OPT_SACK;
	if (tp->rx_opt.wscale_ok) {
		info->tcpi_options |= TCPI_OPT_WSCALE;
		info->tcpi_snd_wscale = tp->rx_opt.snd_wscale;
		info->tcpi_rcv_wscale = tp->rx_opt.rcv_wscale;
	}

	if (tp->ecn_flags&TCP_ECN_OK)
		info->tcpi_options |= TCPI_OPT_ECN;

	info->tcpi_rto = jiffies_to_usecs(icsk->icsk_rto);
	info->tcpi_ato = jiffies_to_usecs(icsk->icsk_ack.ato);
	info->tcpi_snd_mss = tp->mss_cache;
	info->tcpi_rcv_mss = icsk->icsk_ack.rcv_mss;

	if (sk->sk_state == TCP_LISTEN) {
		info->tcpi_unacked = sk->sk_ack_backlog;
		info->tcpi_sacked = sk->sk_max_ack_backlog;
	} else {
		info->tcpi_unacked = tp->packets_out;
		info->tcpi_sacked = tp->sacked_out;
	}
	info->tcpi_lost = tp->lost_out;
	info->tcpi_retrans = tp->retrans_out;
	info->tcpi_fackets = tp->fackets_out;

	info->tcpi_last_data_sent = jiffies_to_msecs(now - tp->lsndtime);
	info->tcpi_last_data_recv = jiffies_to_msecs(now - icsk->icsk_ack.lrcvtime);
	info->tcpi_last_ack_recv = jiffies_to_msecs(now - tp->rcv_tstamp);

	info->tcpi_pmtu = icsk->icsk_pmtu_cookie;
	info->tcpi_rcv_ssthresh = tp->rcv_ssthresh;
	info->tcpi_rtt = jiffies_to_usecs(tp->srtt)>>3;
	info->tcpi_rttvar = jiffies_to_usecs(tp->mdev)>>2;
	info->tcpi_snd_ssthresh = tp->snd_ssthresh;
	info->tcpi_snd_cwnd = tp->snd_cwnd;
	info->tcpi_advmss = tp->advmss;
	info->tcpi_reordering = tp->reordering;

	info->tcpi_rcv_rtt = jiffies_to_usecs(tp->rcv_rtt_est.rtt)>>3;
	info->tcpi_rcv_space = tp->rcvq_space.space;

	info->tcpi_total_retrans = tp->total_retrans;
}