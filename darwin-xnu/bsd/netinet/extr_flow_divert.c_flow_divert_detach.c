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
struct socket {int so_flags; struct flow_divert_pcb* so_fd_pcb; } ;
struct flow_divert_pcb {int /*<<< orphan*/ * so; int /*<<< orphan*/ * group; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FDLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDRELEASE (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  FDUNLOCK (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int SOF_FLOW_DIVERT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flow_divert_pcb_remove (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_send_buffered_data (struct flow_divert_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_divert_send_close_if_needed (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  flow_divert_update_closed_state (struct flow_divert_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 

void
flow_divert_detach(struct socket *so)
{
	struct flow_divert_pcb	*fd_cb		= so->so_fd_pcb;

	VERIFY((so->so_flags & SOF_FLOW_DIVERT) && so->so_fd_pcb != NULL);

	so->so_flags &= ~SOF_FLOW_DIVERT;
	so->so_fd_pcb = NULL;

	FDLOG(LOG_INFO, fd_cb, "Detaching, ref count = %d", fd_cb->ref_count);

	if (fd_cb->group != NULL) {
		/* Last-ditch effort to send any buffered data */
		flow_divert_send_buffered_data(fd_cb, TRUE);

		flow_divert_update_closed_state(fd_cb, SHUT_RDWR, FALSE);
		flow_divert_send_close_if_needed(fd_cb);
		/* Remove from the group */
		flow_divert_pcb_remove(fd_cb);
	}

	socket_unlock(so, 0);
	FDLOCK(fd_cb);
	fd_cb->so = NULL;
	FDUNLOCK(fd_cb);
	socket_lock(so, 0);

	FDRELEASE(fd_cb);	/* Release the socket's reference */
}