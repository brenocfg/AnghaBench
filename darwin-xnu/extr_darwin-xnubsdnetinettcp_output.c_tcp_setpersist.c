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
struct tcpcb {int t_srtt; int t_rttvar; scalar_t__ t_persist_timeout; scalar_t__* t_timer; scalar_t__ t_persist_stop; size_t t_rxtshift; } ;

/* Variables and functions */
 scalar_t__ OFFSET_FROM_START (struct tcpcb*,scalar_t__) ; 
 int /*<<< orphan*/  TCPTV_PERSMAX ; 
 size_t TCPT_PERSIST ; 
 int /*<<< orphan*/  TCPT_RANGESET (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TCP_MAXRXTSHIFT ; 
 int* tcp_backoff ; 
 scalar_t__ tcp_now ; 
 int /*<<< orphan*/  tcptv_persmin_val ; 

void
tcp_setpersist(struct tcpcb *tp)
{
	int t = ((tp->t_srtt >> 2) + tp->t_rttvar) >> 1;

	/* If a PERSIST_TIMER option was set we will limit the
	 * time the persist timer will be active for that connection
	 * in order to avoid DOS by using zero window probes.
	 * see rdar://5805356
	 */

	if ((tp->t_persist_timeout != 0) &&
       	    (tp->t_timer[TCPT_PERSIST] == 0) &&
       	    (tp->t_persist_stop == 0)) {
		tp->t_persist_stop = tcp_now + tp->t_persist_timeout;
	}

	/*
	 * Start/restart persistance timer.
	 */
	TCPT_RANGESET(tp->t_timer[TCPT_PERSIST],
	    t * tcp_backoff[tp->t_rxtshift],
	    tcptv_persmin_val, TCPTV_PERSMAX, 0);
	tp->t_timer[TCPT_PERSIST] = OFFSET_FROM_START(tp, tp->t_timer[TCPT_PERSIST]);

	if (tp->t_rxtshift < TCP_MAXRXTSHIFT)
		tp->t_rxtshift++;
}