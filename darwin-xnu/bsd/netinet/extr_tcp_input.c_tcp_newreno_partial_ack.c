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
typedef  int /*<<< orphan*/  tcp_seq ;
struct tcphdr {int /*<<< orphan*/  th_ack; } ;
struct tcpcb {scalar_t__ t_maxseg; scalar_t__ snd_cwnd; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  t_flags; scalar_t__ t_rtttime; scalar_t__* t_timer; } ;

/* Variables and functions */
 scalar_t__ BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TCPT_PTO ; 
 size_t TCPT_REXMT ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  tcp_output (struct tcpcb*) ; 

__attribute__((used)) static void
tcp_newreno_partial_ack(struct tcpcb *tp, struct tcphdr *th)
{
		tcp_seq onxt = tp->snd_nxt;
		u_int32_t  ocwnd = tp->snd_cwnd;
		tp->t_timer[TCPT_REXMT] = 0;
		tp->t_timer[TCPT_PTO] = 0;
		tp->t_rtttime = 0;
		tp->snd_nxt = th->th_ack;
		/*
		 * Set snd_cwnd to one segment beyond acknowledged offset
		 * (tp->snd_una has not yet been updated when this function
		 *  is called)
		 */
		tp->snd_cwnd = tp->t_maxseg + BYTES_ACKED(th, tp);
		tp->t_flags |= TF_ACKNOW;
		(void) tcp_output(tp);
		tp->snd_cwnd = ocwnd;
		if (SEQ_GT(onxt, tp->snd_nxt))
			tp->snd_nxt = onxt;
		/*
		 * Partial window deflation.  Relies on fact that tp->snd_una
		 * not updated yet.
		 */
		if (tp->snd_cwnd > BYTES_ACKED(th, tp))
			tp->snd_cwnd -= BYTES_ACKED(th, tp);
		else
			tp->snd_cwnd = 0;
		tp->snd_cwnd += tp->t_maxseg;
}