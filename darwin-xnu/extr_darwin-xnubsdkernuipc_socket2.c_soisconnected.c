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
struct socket {int so_state; int /*<<< orphan*/  so_timeo; int /*<<< orphan*/  so_incqlen; int /*<<< orphan*/  so_comp; int /*<<< orphan*/  so_incomp; struct socket* so_head; TYPE_1__* so_proto; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pr_getlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_RCONN ; 
 int /*<<< orphan*/  EV_WCONN ; 
 int SO_FILT_HINT_CONNECTED ; 
 int SO_FILT_HINT_CONNINFO_UPDATED ; 
 int SO_FILT_HINT_LOCKED ; 
 int SS_COMP ; 
 int SS_INCOMP ; 
 int SS_ISCONFIRMING ; 
 int SS_ISCONNECTED ; 
 int SS_ISCONNECTING ; 
 int SS_ISDISCONNECTING ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postevent (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sflt_notify (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_acquire_accept_list (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  so_list ; 
 int /*<<< orphan*/  so_release_accept_list (struct socket*) ; 
 int /*<<< orphan*/  sock_evt_connected ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  soevent (struct socket*,int) ; 
 int /*<<< orphan*/  soreserve_preconnect (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

void
soisconnected(struct socket *so)
{
	so->so_state &= ~(SS_ISCONNECTING|SS_ISDISCONNECTING|SS_ISCONFIRMING);
	so->so_state |= SS_ISCONNECTED;

	soreserve_preconnect(so, 0);

	sflt_notify(so, sock_evt_connected, NULL);

	if (so->so_head != NULL && (so->so_state & SS_INCOMP)) {
		struct socket *head = so->so_head;
		int locked = 0;
		
		/*
		 * Enforce lock order when the protocol has per socket locks
		 */
		if (head->so_proto->pr_getlock != NULL) {
			socket_lock(head, 1);
			so_acquire_accept_list(head, so);
			locked = 1;
		}
		if (so->so_head == head && (so->so_state & SS_INCOMP)) {
			so->so_state &= ~SS_INCOMP;
			so->so_state |= SS_COMP;
			TAILQ_REMOVE(&head->so_incomp, so, so_list);
			TAILQ_INSERT_TAIL(&head->so_comp, so, so_list);
			head->so_incqlen--;

			/*
			 * We have to release the accept list in
			 * case a socket callback calls sock_accept()
			 */
			if (locked != 0) {
				so_release_accept_list(head);
				socket_unlock(so, 0);
			}
			postevent(head, 0, EV_RCONN);
			sorwakeup(head);
			wakeup_one((caddr_t)&head->so_timeo);

			if (locked != 0) {
				socket_unlock(head, 1);
				socket_lock(so, 0);
			}
		} else if (locked != 0) {
			so_release_accept_list(head);
			socket_unlock(head, 1);
		}
	} else {
		postevent(so, 0, EV_WCONN);
		wakeup((caddr_t)&so->so_timeo);
		sorwakeup(so);
		sowwakeup(so);
		soevent(so, SO_FILT_HINT_LOCKED | SO_FILT_HINT_CONNECTED |
		    SO_FILT_HINT_CONNINFO_UPDATED);
	}
}