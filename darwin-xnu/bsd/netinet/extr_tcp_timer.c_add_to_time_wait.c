#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {TYPE_4__* t_inpcb; } ;
struct inpcbinfo {int /*<<< orphan*/  ipi_lock; } ;
struct TYPE_6__ {TYPE_1__* inp_socket; } ;
struct TYPE_5__ {int so_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPCB_TIMER_LAZY ; 
 int SO_NOWAKEFROMSLEEP ; 
 int /*<<< orphan*/  add_to_time_wait_locked (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inpcb_gc_sched (struct inpcbinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_try_lock_exclusive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstat_pcb_detach (TYPE_4__*) ; 
 int /*<<< orphan*/  socket_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_post_kev_msg_closed (TYPE_1__*) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct inpcbinfo tcbinfo ; 

void
add_to_time_wait(struct tcpcb *tp, uint32_t delay)
{
	struct inpcbinfo *pcbinfo = &tcbinfo;
	if (tp->t_inpcb->inp_socket->so_options & SO_NOWAKEFROMSLEEP)
		socket_post_kev_msg_closed(tp->t_inpcb->inp_socket);

	/* 19182803: Notify nstat that connection is closing before waiting. */
	nstat_pcb_detach(tp->t_inpcb);

	if (!lck_rw_try_lock_exclusive(pcbinfo->ipi_lock)) {
		socket_unlock(tp->t_inpcb->inp_socket, 0);
		lck_rw_lock_exclusive(pcbinfo->ipi_lock);
		socket_lock(tp->t_inpcb->inp_socket, 0);
	}
	add_to_time_wait_locked(tp, delay);
	lck_rw_done(pcbinfo->ipi_lock);

	inpcb_gc_sched(pcbinfo, INPCB_TIMER_LAZY);
}