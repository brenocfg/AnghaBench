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
struct socket {int /*<<< orphan*/  so_flags; } ;
struct inpcb {int inp_flags; struct socket* inp_socket; } ;

/* Variables and functions */
 int INP_FLOW_CONTROLLED ; 
 int INP_FLOW_SUSPENDED ; 
 scalar_t__ INP_IS_FLOW_SUSPENDED (struct inpcb*) ; 
 scalar_t__ INP_WAIT_FOR_IF_FEEDBACK (struct inpcb*) ; 
 int /*<<< orphan*/  SOF_SUSPENDED ; 
 int SO_FILT_HINT_LOCKED ; 
 int SO_FILT_HINT_RESUME ; 
 int /*<<< orphan*/  soevent (struct socket*,int) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 

void
inp_reset_fc_state(struct inpcb *inp)
{
	struct socket *so = inp->inp_socket;
	int suspended = (INP_IS_FLOW_SUSPENDED(inp)) ? 1 : 0;
	int needwakeup = (INP_WAIT_FOR_IF_FEEDBACK(inp)) ? 1 : 0;

	inp->inp_flags &= ~(INP_FLOW_CONTROLLED | INP_FLOW_SUSPENDED);

	if (suspended) {
		so->so_flags &= ~(SOF_SUSPENDED);
		soevent(so, (SO_FILT_HINT_LOCKED | SO_FILT_HINT_RESUME));
	}

	/* Give a write wakeup to unblock the socket */
	if (needwakeup)
		sowwakeup(so);
}