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
struct tcpcb {int t_flags; int t_flagsext; int t_maxseg; scalar_t__ snd_ssthresh; scalar_t__ snd_cwnd; scalar_t__ t_rtttime; scalar_t__* t_timer; scalar_t__ snd_max; scalar_t__ snd_recover; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pre_fr ) (struct tcpcb*) ;} ;

/* Variables and functions */
 TYPE_1__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  ENTER_FASTRECOVERY (struct tcpcb*) ; 
 size_t TCPT_PTO ; 
 size_t TCPT_REXMT ; 
 int TF_CWND_NONVALIDATED ; 
 int TF_SENTFIN ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_cc_adjust_nonvalidated_cwnd (struct tcpcb*) ; 
 int tcprexmtthresh ; 

__attribute__((used)) static void
tcp_reduce_congestion_window(
	struct tcpcb	*tp)
{
	/*
	 * If the current tcp cc module has
	 * defined a hook for tasks to run
	 * before entering FR, call it
	 */
	if (CC_ALGO(tp)->pre_fr != NULL)
		CC_ALGO(tp)->pre_fr(tp);
	ENTER_FASTRECOVERY(tp);
	if (tp->t_flags & TF_SENTFIN)
		tp->snd_recover = tp->snd_max - 1;
	else
		tp->snd_recover = tp->snd_max;
	tp->t_timer[TCPT_REXMT] = 0;
	tp->t_timer[TCPT_PTO] = 0;
	tp->t_rtttime = 0;
	if (tp->t_flagsext & TF_CWND_NONVALIDATED) {
		tcp_cc_adjust_nonvalidated_cwnd(tp);
	} else {
		tp->snd_cwnd = tp->snd_ssthresh +
		    tp->t_maxseg * tcprexmtthresh;
	}
}