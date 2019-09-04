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
struct socket {int dummy; } ;
struct inpcb {scalar_t__ inp_sndinprog_cnt; int /*<<< orphan*/  inp_flags; struct socket* inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_FC_FEEDBACK ; 
 int /*<<< orphan*/  INP_WAIT_FOR_IF_FEEDBACK (struct inpcb*) ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 scalar_t__ WNT_STOPUSING ; 
 scalar_t__ in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inp_fc_unthrottle_tcp (struct inpcb*) ; 
 int /*<<< orphan*/  inp_reset_fc_state (struct inpcb*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static void
inp_fc_feedback(struct inpcb *inp)
{
	struct socket *so = inp->inp_socket;

	/* we already hold a want_cnt on this inp, socket can't be null */
	VERIFY(so != NULL);
	socket_lock(so, 1);

	if (in_pcb_checkstate(inp, WNT_RELEASE, 1) == WNT_STOPUSING) {
		socket_unlock(so, 1);
		return;
	}

	if (inp->inp_sndinprog_cnt > 0)
		inp->inp_flags |= INP_FC_FEEDBACK;

	/*
	 * Return if the connection is not in flow-controlled state.
	 * This can happen if the connection experienced
	 * loss while it was in flow controlled state
	 */
	if (!INP_WAIT_FOR_IF_FEEDBACK(inp)) {
		socket_unlock(so, 1);
		return;
	}
	inp_reset_fc_state(inp);

	if (SOCK_TYPE(so) == SOCK_STREAM)
		inp_fc_unthrottle_tcp(inp);

	socket_unlock(so, 1);
}