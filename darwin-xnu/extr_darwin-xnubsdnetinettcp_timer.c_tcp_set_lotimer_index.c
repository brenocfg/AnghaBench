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
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {size_t index; size_t mode; scalar_t__ runtime; scalar_t__ timer_start; } ;
struct tcpcb {scalar_t__* t_timer; TYPE_1__ tentry; } ;

/* Variables and functions */
 size_t TCPT_NONE ; 
 size_t TCPT_NTIMERS ; 
 int /*<<< orphan*/  TCP_SET_TIMER_MODE (size_t,size_t) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static inline void
tcp_set_lotimer_index(struct tcpcb *tp)
{
	uint16_t i, lo_index = TCPT_NONE, mode = 0;
	uint32_t lo_timer = 0;
	for (i = 0; i < TCPT_NTIMERS; ++i) {
		if (tp->t_timer[i] != 0) {
			TCP_SET_TIMER_MODE(mode, i);
			if (lo_timer == 0 || tp->t_timer[i] < lo_timer) {
				lo_timer = tp->t_timer[i];
				lo_index = i;
			}
		}
	}
	tp->tentry.index = lo_index;
	tp->tentry.mode = mode;
	VERIFY(tp->tentry.index == TCPT_NONE || tp->tentry.mode > 0);

	if (tp->tentry.index != TCPT_NONE) {
		tp->tentry.runtime = tp->tentry.timer_start
		    + tp->t_timer[tp->tentry.index];
		if (tp->tentry.runtime == 0)
			tp->tentry.runtime++;
	}
}