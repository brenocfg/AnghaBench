#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct tcphdr {scalar_t__ th_ack; } ;
struct tcpcb {int t_flags; scalar_t__ t_rtttime; int /*<<< orphan*/  t_badrexmt_time; int /*<<< orphan*/  t_flagsext; scalar_t__ snd_max; scalar_t__ snd_nxt; int /*<<< orphan*/  snd_recover_prev; int /*<<< orphan*/  snd_recover; scalar_t__ snd_cwnd; scalar_t__ t_lossflightsize; int /*<<< orphan*/  snd_ssthresh_prev; int /*<<< orphan*/  snd_ssthresh; scalar_t__ snd_cwnd_prev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cwnd_init ) (struct tcpcb*) ;} ;

/* Variables and functions */
 scalar_t__ BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 TYPE_1__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  ENTER_FASTRECOVERY (struct tcpcb*) ; 
 int /*<<< orphan*/  TCP_CC_CWND_INIT_BYTES ; 
 int /*<<< orphan*/  TF_RECOMPUTE_RTT ; 
 int TF_WASFRECOVERY ; 
 scalar_t__ TSTMP_SUPPORTED (struct tcpcb*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_bad_rexmt_fix_sndbuf (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_now ; 

__attribute__((used)) static void
tcp_bad_rexmt_restore_state(struct tcpcb *tp, struct tcphdr *th)
{
	if (TSTMP_SUPPORTED(tp)) {
		u_int32_t fsize, acked;
		fsize = tp->snd_max - th->th_ack;
		acked = BYTES_ACKED(th, tp);

		/*
		 * Implement bad retransmit recovery as
		 * described in RFC 4015.
		 */
		tp->snd_ssthresh = tp->snd_ssthresh_prev;

		/* Initialize cwnd to the initial window */
		if (CC_ALGO(tp)->cwnd_init != NULL)
			CC_ALGO(tp)->cwnd_init(tp);

		tp->snd_cwnd = fsize + min(acked, tp->snd_cwnd);

	} else {
		tp->snd_cwnd = tp->snd_cwnd_prev;
		tp->snd_ssthresh = tp->snd_ssthresh_prev;
		if (tp->t_flags & TF_WASFRECOVERY)
			ENTER_FASTRECOVERY(tp);

		/* Do not use the loss flight size in this case */
		tp->t_lossflightsize = 0;
	}
	tp->snd_cwnd = max(tp->snd_cwnd, TCP_CC_CWND_INIT_BYTES);
	tp->snd_recover = tp->snd_recover_prev;
	tp->snd_nxt = tp->snd_max;

	/* Fix send socket buffer to reflect the change in cwnd */
	tcp_bad_rexmt_fix_sndbuf(tp);

	/*
	 * This RTT might reflect the extra delay induced
	 * by the network. Skip using this sample for RTO
	 * calculation and mark the connection so we can
	 * recompute RTT when the next eligible sample is
	 * found.
	 */
	tp->t_flagsext |= TF_RECOMPUTE_RTT;
	tp->t_badrexmt_time = tcp_now;
	tp->t_rtttime = 0;
}