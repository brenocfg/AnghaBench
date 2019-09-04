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
typedef  scalar_t__ uint32_t ;
struct tcpcb {scalar_t__* t_timer; struct inpcb* t_inpcb; } ;
struct inpcbinfo {int /*<<< orphan*/  ipi_twcount; int /*<<< orphan*/  ipi_lock; } ;
struct inpcb {int inp_flags2; } ;

/* Variables and functions */
 int INP2_TIMEWAIT ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct tcpcb*,int /*<<< orphan*/ ) ; 
 size_t TCPT_2MSL ; 
 scalar_t__ TIMER_IS_ON_LIST (struct tcpcb*) ; 
 int /*<<< orphan*/  inp_list ; 
 int /*<<< orphan*/  t_twentry ; 
 struct inpcbinfo tcbinfo ; 
 scalar_t__ tcp_now ; 
 int /*<<< orphan*/  tcp_remove_timer (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_tw_tailq ; 

__attribute__((used)) static void
add_to_time_wait_locked(struct tcpcb *tp, uint32_t delay)
{
	struct inpcbinfo *pcbinfo = &tcbinfo;
	struct inpcb *inp = tp->t_inpcb;
	uint32_t timer;

	/* pcb list should be locked when we get here */
	LCK_RW_ASSERT(pcbinfo->ipi_lock, LCK_RW_ASSERT_EXCLUSIVE);

	/* We may get here multiple times, so check */
	if (!(inp->inp_flags2 & INP2_TIMEWAIT)) {
		pcbinfo->ipi_twcount++;
		inp->inp_flags2 |= INP2_TIMEWAIT;

		/* Remove from global inp list */
		LIST_REMOVE(inp, inp_list);
	} else {
		TAILQ_REMOVE(&tcp_tw_tailq, tp, t_twentry);
	}

	/* Compute the time at which this socket can be closed */
	timer = tcp_now + delay;

	/* We will use the TCPT_2MSL timer for tracking this delay */

	if (TIMER_IS_ON_LIST(tp))
		tcp_remove_timer(tp);
	tp->t_timer[TCPT_2MSL] = timer;

	TAILQ_INSERT_TAIL(&tcp_tw_tailq, tp, t_twentry);
}