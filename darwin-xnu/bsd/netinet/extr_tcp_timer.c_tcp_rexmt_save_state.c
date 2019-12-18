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
typedef  scalar_t__ u_int32_t ;
struct tcpcb {int t_srtt_prev; int t_srtt; int t_rttvar_prev; int t_rttvar; int /*<<< orphan*/  t_flagsext; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  snd_recover; int /*<<< orphan*/  snd_recover_prev; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_ssthresh_prev; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_cwnd_prev; scalar_t__ snd_una; scalar_t__ snd_max; } ;

/* Variables and functions */
 scalar_t__ IN_FASTRECOVERY (struct tcpcb*) ; 
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 
 int /*<<< orphan*/  TF_RECOMPUTE_RTT ; 
 int /*<<< orphan*/  TF_WASFRECOVERY ; 
 scalar_t__ TSTMP_SUPPORTED (struct tcpcb*) ; 
 int /*<<< orphan*/  max (scalar_t__,int /*<<< orphan*/ ) ; 

void
tcp_rexmt_save_state(struct tcpcb *tp)
{
	u_int32_t fsize;
	if (TSTMP_SUPPORTED(tp)) {
		/*
		 * Since timestamps are supported on the connection,
		 * we can do recovery as described in rfc 4015.
		 */
		fsize = tp->snd_max - tp->snd_una;
		tp->snd_ssthresh_prev = max(fsize, tp->snd_ssthresh);
		tp->snd_recover_prev = tp->snd_recover;
	} else {
		/*
		 * Timestamp option is not supported on this connection.
		 * Record ssthresh and cwnd so they can
		 * be recovered if this turns out to be a "bad" retransmit.
		 * A retransmit is considered "bad" if an ACK for this
		 * segment is received within RTT/2 interval; the assumption
		 * here is that the ACK was already in flight.  See
		 * "On Estimating End-to-End Network Path Properties" by
		 * Allman and Paxson for more details.
		 */
		tp->snd_cwnd_prev = tp->snd_cwnd;
		tp->snd_ssthresh_prev = tp->snd_ssthresh;
		tp->snd_recover_prev = tp->snd_recover;
		if (IN_FASTRECOVERY(tp))
			tp->t_flags |= TF_WASFRECOVERY;
		else
			tp->t_flags &= ~TF_WASFRECOVERY;
	}
	tp->t_srtt_prev = (tp->t_srtt >> TCP_RTT_SHIFT) + 2;
	tp->t_rttvar_prev = (tp->t_rttvar >> TCP_RTTVAR_SHIFT);
	tp->t_flagsext &= ~(TF_RECOMPUTE_RTT);
}