#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct TYPE_5__ {scalar_t__ index; scalar_t__ runtime; scalar_t__ mode; scalar_t__ timer_start; } ;
struct tcpcb {scalar_t__* t_timer; TYPE_2__ tentry; int /*<<< orphan*/  t_flagsext; TYPE_3__* t_inpcb; } ;
struct socket {int dummy; } ;
typedef  int /*<<< orphan*/  needtorun ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {TYPE_1__* inp_last_outifp; struct socket* inp_socket; } ;
struct TYPE_4__ {scalar_t__ if_index; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TCPT_NONE ; 
 int TCPT_NTIMERS ; 
 size_t TCPT_PTO ; 
 int /*<<< orphan*/  TCP_SET_TIMER_MODE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TF_PROBING ; 
 scalar_t__ TIMER_IS_ON_LIST (struct tcpcb*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 scalar_t__ WNT_STOPUSING ; 
 int /*<<< orphan*/  bzero (scalar_t__*,int) ; 
 scalar_t__ in_pcb_checkstate (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 scalar_t__ tcp_now ; 
 int /*<<< orphan*/  tcp_remove_timer (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_set_lotimer_index (struct tcpcb*) ; 
 struct tcpcb* tcp_timers (struct tcpcb*,scalar_t__) ; 
 scalar_t__ timer_diff (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

u_int32_t
tcp_run_conn_timer(struct tcpcb *tp, u_int16_t *te_mode,
	u_int16_t probe_if_index)
{
	struct socket *so;
	u_int16_t i = 0, index = TCPT_NONE, lo_index = TCPT_NONE;
	u_int32_t timer_val, offset = 0, lo_timer = 0;
	int32_t diff;
	boolean_t needtorun[TCPT_NTIMERS];
	int count = 0;

	VERIFY(tp != NULL);
	bzero(needtorun, sizeof(needtorun));
	*te_mode = 0;

	socket_lock(tp->t_inpcb->inp_socket, 1);

	so = tp->t_inpcb->inp_socket;
	/* Release the want count on inp */
	if (in_pcb_checkstate(tp->t_inpcb, WNT_RELEASE, 1)
		== WNT_STOPUSING) {
		if (TIMER_IS_ON_LIST(tp)) {
			tcp_remove_timer(tp);
		}

		/* Looks like the TCP connection got closed while we
		 * were waiting for the lock.. Done
		 */
		goto done;
	}

	/*
	 * If this connection is over an interface that needs to
	 * be probed, send probe packets to reinitiate communication.
	 */
	if (probe_if_index > 0 && tp->t_inpcb->inp_last_outifp != NULL &&
	    tp->t_inpcb->inp_last_outifp->if_index == probe_if_index) {
		tp->t_flagsext |= TF_PROBING;
		tcp_timers(tp, TCPT_PTO);
		tp->t_timer[TCPT_PTO] = 0;
		tp->t_flagsext &= ~TF_PROBING;
	}

	/*
	 * Since the timer thread needs to wait for tcp lock, it may race
	 * with another thread that can cancel or reschedule the timer
	 * that is about to run. Check if we need to run anything.
	 */
	if ((index = tp->tentry.index) == TCPT_NONE)
		goto done;

	timer_val = tp->t_timer[index];

	diff = timer_diff(tp->tentry.runtime, 0, tcp_now, 0);
	if (diff > 0) {
		if (tp->tentry.index != TCPT_NONE) {
			offset = diff;
			*(te_mode) = tp->tentry.mode;
		}
		goto done;
	}

	tp->t_timer[index] = 0;
	if (timer_val > 0) {
		tp = tcp_timers(tp, index);
		if (tp == NULL)
			goto done;
	}

	/*
	 * Check if there are any other timers that need to be run.
	 * While doing it, adjust the timer values wrt tcp_now.
	 */
	tp->tentry.mode = 0;
	for (i = 0; i < TCPT_NTIMERS; ++i) {
		if (tp->t_timer[i] != 0) {
			diff = timer_diff(tp->tentry.timer_start,
				tp->t_timer[i], tcp_now, 0);
			if (diff <= 0) {
				needtorun[i] = TRUE;
				count++;
			} else {
				tp->t_timer[i] = diff;
				needtorun[i] = FALSE;
				if (lo_timer == 0 || diff < lo_timer) {
					lo_timer = diff;
					lo_index = i;
				}
				TCP_SET_TIMER_MODE(tp->tentry.mode, i);
			}
		}
	}

	tp->tentry.timer_start = tcp_now;
	tp->tentry.index = lo_index;
	VERIFY(tp->tentry.index == TCPT_NONE || tp->tentry.mode > 0);

	if (tp->tentry.index != TCPT_NONE) {
		tp->tentry.runtime = tp->tentry.timer_start +
			tp->t_timer[tp->tentry.index];
		if (tp->tentry.runtime == 0)
			tp->tentry.runtime++;
	}

	if (count > 0) {
		/* run any other timers outstanding at this time. */
		for (i = 0; i < TCPT_NTIMERS; ++i) {
			if (needtorun[i]) {
				tp->t_timer[i] = 0;
				tp = tcp_timers(tp, i);
				if (tp == NULL) {
					offset = 0;
					*(te_mode) = 0;
					goto done;
				}
			}
		}
		tcp_set_lotimer_index(tp);
	}

	if (tp->tentry.index < TCPT_NONE) {
		offset = tp->t_timer[tp->tentry.index];
		*(te_mode) = tp->tentry.mode;
	}

done:
	if (tp != NULL && tp->tentry.index == TCPT_NONE) {
		tcp_remove_timer(tp);
		offset = 0;
	}

	socket_unlock(so, 1);
	return(offset);
}