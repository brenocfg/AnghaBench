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
struct tcphdr {scalar_t__ th_ack; } ;
struct tcpcb {scalar_t__ snd_max; scalar_t__ t_bytes_acked; scalar_t__ snd_ssthresh; scalar_t__ snd_cwnd; scalar_t__ t_maxseg; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ max (scalar_t__,scalar_t__) ; 

void
tcp_newreno_post_fr(struct tcpcb *tp, struct tcphdr *th) {
	int32_t ss;

	ss = tp->snd_max - th->th_ack;

	/*
	 * Complete ack.  Inflate the congestion window to
	 * ssthresh and exit fast recovery.
	 *
	 * Window inflation should have left us with approx.
	 * snd_ssthresh outstanding data.  But in case we
	 * would be inclined to send a burst, better to do
	 * it via the slow start mechanism.
	 *
	 * If the flight size is zero, then make congestion 
	 * window to be worth at least 2 segments to avoid 
	 * delayed acknowledgement (draft-ietf-tcpm-rfc3782-bis-05).
	 */
	if (ss < (int32_t)tp->snd_ssthresh)
		tp->snd_cwnd = max(ss, tp->t_maxseg) + tp->t_maxseg;
	else
		tp->snd_cwnd = tp->snd_ssthresh;
	tp->t_bytes_acked = 0;
}