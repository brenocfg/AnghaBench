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
struct socket {int /*<<< orphan*/  so_state; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int ECONNABORTED ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL ; 
 int /*<<< orphan*/  SS_NOFDREF ; 
 int /*<<< orphan*/  current_proc () ; 
 int sflt_accept (struct socket*,struct socket*,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  sock_freeaddr (struct sockaddr*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 scalar_t__ sogetaddr_locked (struct socket*,struct sockaddr**,int) ; 
 int /*<<< orphan*/  sosetdefunct (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
soacceptfilter(struct socket *so, struct socket *head)
{
	struct sockaddr *local = NULL, *remote = NULL;
	int error = 0;

	/*
	 * Hold the lock even if this socket has not been made visible
	 * to the filter(s).  For sockets with global locks, this protects
	 * against the head or peer going away
	 */
	socket_lock(so, 1);
	if (sogetaddr_locked(so, &remote, 1) != 0 ||
	    sogetaddr_locked(so, &local, 0) != 0) {
		so->so_state &= ~SS_NOFDREF;
		socket_unlock(so, 1);
		soclose(so);
		/* Out of resources; try it again next time */
		error = ECONNABORTED;
		goto done;
	}

	error = sflt_accept(head, so, local, remote);

	/*
	 * If we get EJUSTRETURN from one of the filters, mark this socket
	 * as inactive and return it anyway.  This newly accepted socket
	 * will be disconnected later before we hand it off to the caller.
	 */
	if (error == EJUSTRETURN) {
		error = 0;
		(void) sosetdefunct(current_proc(), so,
		    SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL, FALSE);
	}

	if (error != 0) {
		/*
		 * This may seem like a duplication to the above error
		 * handling part when we return ECONNABORTED, except
		 * the following is done while holding the lock since
		 * the socket has been exposed to the filter(s) earlier.
		 */
		so->so_state &= ~SS_NOFDREF;
		socket_unlock(so, 1);
		soclose(so);
		/* Propagate socket filter's error code to the caller */
	} else {
		socket_unlock(so, 1);
	}
done:
	/* Callee checks for NULL pointer */
	sock_freeaddr(remote);
	sock_freeaddr(local);
	return (error);
}