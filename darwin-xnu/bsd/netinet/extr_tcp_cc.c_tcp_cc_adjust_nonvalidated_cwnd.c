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
struct tcpcb {int t_pipeack; int snd_cwnd; int t_maxseg; int /*<<< orphan*/  t_flagsext; int /*<<< orphan*/  t_lossflightsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CC_CWND_INIT_BYTES ; 
 int /*<<< orphan*/  TF_CWND_NONVALIDATED ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_clear_pipeack_state (struct tcpcb*) ; 
 int tcp_get_max_pipeack (struct tcpcb*) ; 
 int tcprexmtthresh ; 

inline void
tcp_cc_adjust_nonvalidated_cwnd(struct tcpcb *tp)
{
	tp->t_pipeack = tcp_get_max_pipeack(tp);
	tcp_clear_pipeack_state(tp);
	tp->snd_cwnd = (max(tp->t_pipeack, tp->t_lossflightsize) >> 1);
	tp->snd_cwnd = max(tp->snd_cwnd, TCP_CC_CWND_INIT_BYTES);
	tp->snd_cwnd += tp->t_maxseg * tcprexmtthresh;
	tp->t_flagsext &= ~TF_CWND_NONVALIDATED;
}