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
struct tcpcb {scalar_t__ tcp_cc_index; struct tcp_ccstate* t_ccstate; } ;
struct tcp_ccstate {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCP_CC_ALGO_CUBIC_INDEX ; 
 scalar_t__ TCP_CC_ALGO_NEWRENO_INDEX ; 
 int /*<<< orphan*/  bzero (struct tcp_ccstate*,int) ; 
 int /*<<< orphan*/  tcp_cc_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

void
tcp_cc_allocate_state(struct tcpcb *tp)
{
	if (tp->tcp_cc_index == TCP_CC_ALGO_CUBIC_INDEX &&
		tp->t_ccstate == NULL) {
		tp->t_ccstate = (struct tcp_ccstate *)zalloc(tcp_cc_zone);

		/*
		 * If we could not allocate memory for congestion control
		 * state, revert to using TCP NewReno as it does not
		 * require any state
		 */
		if (tp->t_ccstate == NULL)
			tp->tcp_cc_index = TCP_CC_ALGO_NEWRENO_INDEX;
		else
			bzero(tp->t_ccstate, sizeof(*tp->t_ccstate));
	}
}