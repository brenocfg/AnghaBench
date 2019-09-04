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
struct unpcb {scalar_t__ rw_thrcount; int /*<<< orphan*/  unp_flags; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNP_DONTDISCONNECT ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  wakeup (struct unpcb*) ; 

__attribute__((used)) static void
unp_get_locks_in_order(struct socket *so, struct socket *conn_so)
{
	if (so < conn_so) {
		socket_lock(conn_so, 1);
	} else {
		struct unpcb *unp = sotounpcb(so);
		unp->unp_flags |= UNP_DONTDISCONNECT;
		unp->rw_thrcount++;
		socket_unlock(so, 0);

		/* Get the locks in the correct order */
		socket_lock(conn_so, 1);
		socket_lock(so, 0);
		unp->rw_thrcount--;
		if (unp->rw_thrcount == 0) {
			unp->unp_flags &= ~UNP_DONTDISCONNECT;
			wakeup(unp);
		}
	}
}