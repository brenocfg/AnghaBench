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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_char ;
struct tcpcb {scalar_t__ tcp_cc_index; } ;
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* switch_to ) (struct tcpcb*,scalar_t__) ;int /*<<< orphan*/  (* cleanup ) (struct tcpcb*) ;} ;

/* Variables and functions */
 TYPE_1__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  TCP_CC_CHANGE_ALGO ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  stub2 (struct tcpcb*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_cc_allocate_state (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_ccdbg_trace (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_set_new_cc(struct socket *so, uint16_t cc_index)
{
	struct inpcb *inp = sotoinpcb(so);
	struct tcpcb *tp = intotcpcb(inp);
	u_char old_cc_index = 0;
	if (tp->tcp_cc_index != cc_index) {

		old_cc_index = tp->tcp_cc_index;

		if (CC_ALGO(tp)->cleanup != NULL)
			CC_ALGO(tp)->cleanup(tp);
		tp->tcp_cc_index = cc_index;

		tcp_cc_allocate_state(tp);

		if (CC_ALGO(tp)->switch_to != NULL)
			CC_ALGO(tp)->switch_to(tp, old_cc_index);

		tcp_ccdbg_trace(tp, NULL, TCP_CC_CHANGE_ALGO);
	}
}