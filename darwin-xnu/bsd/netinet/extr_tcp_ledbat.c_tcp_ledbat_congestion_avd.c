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
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ t_bytes_acked; scalar_t__ snd_cwnd; scalar_t__ t_maxseg; scalar_t__ snd_wnd; } ;

/* Variables and functions */
 int BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 int /*<<< orphan*/  update_cwnd (struct tcpcb*,scalar_t__) ; 

void
tcp_ledbat_congestion_avd(struct tcpcb *tp, struct tcphdr *th) {
	int acked = 0;
	u_int32_t incr = 0;

	acked = BYTES_ACKED(th, tp);
	tp->t_bytes_acked += acked;
	if (tp->t_bytes_acked > tp->snd_cwnd) {
		tp->t_bytes_acked -= tp->snd_cwnd;
		incr = tp->t_maxseg;
	}

	if (tp->snd_cwnd < tp->snd_wnd && incr > 0) {
		update_cwnd(tp, incr);
	}
}