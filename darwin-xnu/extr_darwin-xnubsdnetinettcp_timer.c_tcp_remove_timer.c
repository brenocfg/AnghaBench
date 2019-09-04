#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tcptimerlist {int /*<<< orphan*/  mtx; int /*<<< orphan*/  entries; TYPE_3__* next_te; } ;
struct TYPE_7__ {int /*<<< orphan*/ * le_prev; int /*<<< orphan*/ * le_next; } ;
struct TYPE_8__ {TYPE_2__ le; } ;
struct tcpcb {TYPE_3__ tentry; int /*<<< orphan*/  t_flags; TYPE_1__* t_inpcb; } ;
struct TYPE_6__ {int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 TYPE_3__* LIST_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_TIMER_ONLIST ; 
 int /*<<< orphan*/  TIMER_IS_ON_LIST (struct tcpcb*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le ; 
 int /*<<< orphan*/  socket_lock_assert_owned (int /*<<< orphan*/ ) ; 
 struct tcptimerlist tcp_timer_list ; 

void
tcp_remove_timer(struct tcpcb *tp)
{
	struct tcptimerlist *listp = &tcp_timer_list;

	socket_lock_assert_owned(tp->t_inpcb->inp_socket);
	if (!(TIMER_IS_ON_LIST(tp))) {
		return;
	}
	lck_mtx_lock(listp->mtx);

	/* Check if pcb is on timer list again after acquiring the lock */
	if (!(TIMER_IS_ON_LIST(tp))) {
		lck_mtx_unlock(listp->mtx);
		return;
	}

	if (listp->next_te != NULL && listp->next_te == &tp->tentry)
		listp->next_te = LIST_NEXT(&tp->tentry, le);

	LIST_REMOVE(&tp->tentry, le);
	tp->t_flags &= ~(TF_TIMER_ONLIST);

	listp->entries--;

	tp->tentry.le.le_next = NULL;
	tp->tentry.le.le_prev = NULL;
	lck_mtx_unlock(listp->mtx);
}