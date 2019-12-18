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
typedef  int u_int ;
struct tcpcb {scalar_t__ t_state; int snd_cwnd; int t_maxseg; int snd_ssthresh; int bg_ssthresh; int /*<<< orphan*/  snd_wnd; } ;

/* Variables and functions */
 scalar_t__ TCPS_ESTABLISHED ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_cc_resize_sndbuf (struct tcpcb*) ; 

void
tcp_ledbat_after_timeout(struct tcpcb *tp) {
	if (tp->t_state >=  TCPS_ESTABLISHED) {
		u_int win = min(tp->snd_wnd, tp->snd_cwnd) / 2 / tp->t_maxseg;
		if (win < 2)
			win = 2;
		tp->snd_ssthresh = win * tp->t_maxseg;

		if (tp->bg_ssthresh > tp->snd_ssthresh)
			tp->bg_ssthresh = tp->snd_ssthresh;

		tp->snd_cwnd = tp->t_maxseg;
		tcp_cc_resize_sndbuf(tp);
	}
}