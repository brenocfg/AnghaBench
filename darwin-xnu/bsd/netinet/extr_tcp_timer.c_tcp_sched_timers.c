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
typedef  scalar_t__ u_int16_t ;
struct tcptimerlist {scalar_t__ entries; scalar_t__ maxentries; scalar_t__ pref_mode; scalar_t__ pref_offset; scalar_t__ mode; int /*<<< orphan*/  mtx; scalar_t__ idleruns; int /*<<< orphan*/  runtime; scalar_t__ scheduled; scalar_t__ running; int /*<<< orphan*/  lhead; } ;
struct tcptimerentry {scalar_t__ index; scalar_t__ mode; int /*<<< orphan*/  runtime; } ;
struct tcpcb {int /*<<< orphan*/  t_flags; TYPE_1__* t_inpcb; struct tcptimerentry tentry; } ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ inp_state; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ INPCB_STATE_DEAD ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct tcptimerentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ TCPT_NONE ; 
 scalar_t__ TCP_TIMERLIST_100MS_MODE ; 
 scalar_t__ TCP_TIMERLIST_10MS_MODE ; 
 int /*<<< orphan*/  TCP_TIMER_100MS_QUANTUM ; 
 int /*<<< orphan*/  TCP_TIMER_10MS_QUANTUM ; 
 int /*<<< orphan*/  TF_TIMER_ONLIST ; 
 scalar_t__ TIMER_IS_ON_LIST (struct tcpcb*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERIFY_NEXT_LINK (struct tcptimerentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_PREV_LINK (struct tcptimerentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ need_to_resched_timerlist (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tcp_now ; 
 int /*<<< orphan*/  tcp_remove_timer (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_resched_timerlist ; 
 int /*<<< orphan*/  tcp_sched_timerlist (scalar_t__) ; 
 int /*<<< orphan*/  tcp_timer_advanced ; 
 struct tcptimerlist tcp_timer_list ; 
 scalar_t__ timer_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
tcp_sched_timers(struct tcpcb *tp)
{
	struct tcptimerentry *te = &tp->tentry;
	u_int16_t index = te->index;
	u_int16_t mode = te->mode;
	struct tcptimerlist *listp = &tcp_timer_list;
	int32_t offset = 0;
	boolean_t list_locked = FALSE;

	if (tp->t_inpcb->inp_state == INPCB_STATE_DEAD) {
		/* Just return without adding the dead pcb to the list */
		if (TIMER_IS_ON_LIST(tp)) {
			tcp_remove_timer(tp);
		}
		return;
	}

	if (index == TCPT_NONE) {
		/* Nothing to run */
		tcp_remove_timer(tp);
		return;
	}

	/*
	 * compute the offset at which the next timer for this connection
	 * has to run.
	 */
	offset = timer_diff(te->runtime, 0, tcp_now, 0);
	if (offset <= 0) {
		offset = 1;
		tcp_timer_advanced++;
	}

	if (!TIMER_IS_ON_LIST(tp)) {
		if (!list_locked) {
			lck_mtx_lock(listp->mtx);
			list_locked = TRUE;
		}

		if (!TIMER_IS_ON_LIST(tp)) {
			LIST_INSERT_HEAD(&listp->lhead, te, le);
			tp->t_flags |= TF_TIMER_ONLIST;

			listp->entries++;
			if (listp->entries > listp->maxentries)
				listp->maxentries = listp->entries;

			/* if the list is not scheduled, just schedule it */
			if (!listp->scheduled)
				goto schedule;
		}
	}

	/*
	 * Timer entry is currently on the list, check if the list needs
	 * to be rescheduled.
	 */
	if (need_to_resched_timerlist(te->runtime, mode)) {
		tcp_resched_timerlist++;

		if (!list_locked) {
			lck_mtx_lock(listp->mtx);
			list_locked = TRUE;
		}

		VERIFY_NEXT_LINK(te, le);
		VERIFY_PREV_LINK(te, le);

		if (listp->running) {
			listp->pref_mode |= mode;
			if (listp->pref_offset == 0 ||
				offset < listp->pref_offset) {
				listp->pref_offset = offset;
			}
		} else {
			/*
			 * The list could have got rescheduled while
			 * this thread was waiting for the lock
			 */
			if (listp->scheduled) {
				int32_t diff;
				diff = timer_diff(listp->runtime, 0,
				    tcp_now, offset);
				if (diff <= 0)
					goto done;
				else
					goto schedule;
			} else {
				goto schedule;
			}
		}
	}
	goto done;

schedule:
	/*
	 * Since a connection with timers is getting scheduled, the timer
	 * list moves from idle to active state and that is why idlegen is
	 * reset
	 */
	if (mode & TCP_TIMERLIST_10MS_MODE) {
		listp->mode = TCP_TIMERLIST_10MS_MODE;
		listp->idleruns = 0;
		offset = min(offset, TCP_TIMER_10MS_QUANTUM);
	} else if (mode & TCP_TIMERLIST_100MS_MODE) {
		if (listp->mode > TCP_TIMERLIST_100MS_MODE)
			listp->mode = TCP_TIMERLIST_100MS_MODE;
		listp->idleruns = 0;
		offset = min(offset, TCP_TIMER_100MS_QUANTUM);
	}
	tcp_sched_timerlist(offset);

done:
	if (list_locked)
		lck_mtx_unlock(listp->mtx);

	return;
}