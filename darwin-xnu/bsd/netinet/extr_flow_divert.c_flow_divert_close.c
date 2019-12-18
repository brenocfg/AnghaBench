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
struct socket {int so_flags; int /*<<< orphan*/  so_rcv; struct flow_divert_pcb* so_fd_pcb; } ;
struct flow_divert_pcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FDLOG0 (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ SOCK_TYPE (struct socket*) ; 
 int SOF_FLOW_DIVERT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flow_divert_pcb_remove (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_send_buffered_data (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_send_close_if_needed (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_update_closed_state (struct flow_divert_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soisdisconnecting (struct socket*) ; 

__attribute__((used)) static int
flow_divert_close(struct socket *so)
{
	struct flow_divert_pcb	*fd_cb		= so->so_fd_pcb;

	VERIFY((so->so_flags & SOF_FLOW_DIVERT) && so->so_fd_pcb != NULL);

	FDLOG0(LOG_INFO, fd_cb, "Closing");

	if (SOCK_TYPE(so) == SOCK_STREAM) {
		soisdisconnecting(so);
		sbflush(&so->so_rcv);
	}

	flow_divert_send_buffered_data(fd_cb, TRUE);
	flow_divert_update_closed_state(fd_cb, SHUT_RDWR, FALSE);
	flow_divert_send_close_if_needed(fd_cb);

	/* Remove from the group */
	flow_divert_pcb_remove(fd_cb);

	return 0;
}