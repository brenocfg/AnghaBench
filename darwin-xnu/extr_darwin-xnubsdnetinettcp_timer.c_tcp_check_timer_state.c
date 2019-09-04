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
struct tcpcb {TYPE_1__* t_inpcb; } ;
struct TYPE_2__ {int inp_flags2; int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 int INP2_TIMEWAIT ; 
 int /*<<< orphan*/  socket_lock_assert_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sched_timers (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_set_lotimer_index (struct tcpcb*) ; 

void
tcp_check_timer_state(struct tcpcb *tp)
{
	socket_lock_assert_owned(tp->t_inpcb->inp_socket);

	if (tp->t_inpcb->inp_flags2 & INP2_TIMEWAIT)
		return;

	tcp_set_lotimer_index(tp);

	tcp_sched_timers(tp);
	return;
}