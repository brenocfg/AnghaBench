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
struct TYPE_2__ {int /*<<< orphan*/  index; int /*<<< orphan*/  timer_start; } ;
struct tcpcb {TYPE_1__ tentry; scalar_t__* t_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPT_NONE ; 
 int TCPT_NTIMERS ; 
 int /*<<< orphan*/  tcp_now ; 
 int /*<<< orphan*/  tcp_remove_timer (struct tcpcb*) ; 

void
tcp_canceltimers(struct tcpcb *tp)
{
	int i;

	tcp_remove_timer(tp);
	for (i = 0; i < TCPT_NTIMERS; i++)
		tp->t_timer[i] = 0;
	tp->tentry.timer_start = tcp_now;
	tp->tentry.index = TCPT_NONE;
}