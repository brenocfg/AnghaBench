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
typedef  scalar_t__ uint32_t ;
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ snd_cwnd; scalar_t__ snd_wnd; scalar_t__ t_bytes_acked; scalar_t__ t_maxseg; } ;

/* Variables and functions */
 scalar_t__ BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 

void
tcp_newreno_congestion_avd(struct tcpcb *tp, struct tcphdr *th) {
	uint32_t acked = 0;
	acked = BYTES_ACKED(th, tp);
	/*
	 * Grow the congestion window, if the
	 * connection is cwnd bound.
	 */
	if (tp->snd_cwnd < tp->snd_wnd) {
		tp->t_bytes_acked += acked;
		if (tp->t_bytes_acked > tp->snd_cwnd) {
			tp->t_bytes_acked -= tp->snd_cwnd;
			tp->snd_cwnd += tp->t_maxseg;
		}
	}
}