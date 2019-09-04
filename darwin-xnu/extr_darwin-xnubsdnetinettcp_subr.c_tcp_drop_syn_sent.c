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
struct tcpcb {scalar_t__ t_state; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCPS_SYN_SENT ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  tcp_drop (struct tcpcb*,int) ; 

void
tcp_drop_syn_sent(struct inpcb *inp, int errno)
{
	struct tcpcb *tp = intotcpcb(inp);

	if (tp && tp->t_state == TCPS_SYN_SENT)
		tcp_drop(tp, errno);
}