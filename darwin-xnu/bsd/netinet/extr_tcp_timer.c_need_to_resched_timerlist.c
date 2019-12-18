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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
struct tcptimerlist {int /*<<< orphan*/  runtime; int /*<<< orphan*/  scheduled; scalar_t__ running; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TCP_TIMERLIST_100MS_MODE ; 
 int TCP_TIMERLIST_10MS_MODE ; 
 scalar_t__ TCP_TIMER_100MS_QUANTUM ; 
 scalar_t__ TCP_TIMER_10MS_QUANTUM ; 
 scalar_t__ TCP_TIMER_500MS_QUANTUM ; 
 int /*<<< orphan*/  TRUE ; 
 struct tcptimerlist tcp_timer_list ; 
 scalar_t__ timer_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
need_to_resched_timerlist(u_int32_t runtime, u_int16_t mode)
{
	struct tcptimerlist *listp = &tcp_timer_list;
	int32_t diff;

	/*
	 * If the list is being processed then the state of the list is
	 * in flux. In this case always acquire the lock and set the state
	 * correctly.
	 */
	if (listp->running)
		return (TRUE);

	if (!listp->scheduled)
		return (TRUE);

	diff = timer_diff(listp->runtime, 0, runtime, 0);
	if (diff <= 0) {
		/* The list is going to run before this timer */
		return (FALSE);
	} else {
		if (mode & TCP_TIMERLIST_10MS_MODE) {
			if (diff <= TCP_TIMER_10MS_QUANTUM)
				return (FALSE);
		} else if (mode & TCP_TIMERLIST_100MS_MODE) {
			if (diff <= TCP_TIMER_100MS_QUANTUM)
				return (FALSE);
		} else {
			if (diff <= TCP_TIMER_500MS_QUANTUM)
				return (FALSE);
		}
	}
	return (TRUE);
}