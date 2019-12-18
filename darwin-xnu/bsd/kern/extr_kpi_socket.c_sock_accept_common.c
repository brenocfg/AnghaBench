#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * tqh_first; } ;
struct socket {int so_options; int so_state; scalar_t__ so_error; int so_flags; TYPE_2__* so_proto; int /*<<< orphan*/ * so_filt; int /*<<< orphan*/  so_flags1; int /*<<< orphan*/  so_qlen; int /*<<< orphan*/ * so_head; TYPE_4__ so_comp; int /*<<< orphan*/  so_timeo; } ;
struct sockaddr {int sa_len; } ;
typedef  struct socket* socket_t ;
typedef  int /*<<< orphan*/ * sock_upcall ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_9__ {int /*<<< orphan*/  nas_socket_in_kernel_os_total; int /*<<< orphan*/  nas_socket_in_kernel_total; } ;
struct TYPE_8__ {int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;TYPE_1__* pr_domain; } ;
struct TYPE_7__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 scalar_t__ ECONNABORTED ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOTSUP ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INC_ATOMIC_INT64_LIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_NOTOWNED ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  M_SONAME ; 
 int PCATCH ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 int PSOCK ; 
 int /*<<< orphan*/  SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL ; 
 int /*<<< orphan*/  SOF1_IN_KERNEL_SOCKET ; 
 int SOF_DEFUNCT ; 
 int SO_ACCEPTCONN ; 
 int SS_CANTRCVMORE ; 
 int SS_COMP ; 
 int SS_NBIO ; 
 scalar_t__ TAILQ_EMPTY (TYPE_4__*) ; 
 struct socket* TAILQ_FIRST (TYPE_4__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_4__*,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr*,int) ; 
 scalar_t__ msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__ net_api_stats ; 
 int /*<<< orphan*/  so_acquire_accept_list (struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_list ; 
 int /*<<< orphan*/  so_release_accept_list (struct socket*) ; 
 scalar_t__ soacceptfilter (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  soacceptlock (struct socket*,struct sockaddr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_setupcalls_locked (struct socket*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  sodefunct (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodereference (struct socket*) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (struct socket*,int /*<<< orphan*/ ) ; 

errno_t
sock_accept_common(socket_t sock, struct sockaddr *from, int fromlen, int flags,
    sock_upcall callback, void *cookie, socket_t *new_sock, bool is_internal)
{
	struct sockaddr *sa;
	struct socket *new_so;
	lck_mtx_t *mutex_held;
	int dosocklock;
	errno_t	error = 0;

	if (sock == NULL || new_sock == NULL)
		return (EINVAL);

	socket_lock(sock, 1);
	if ((sock->so_options & SO_ACCEPTCONN) == 0) {
		socket_unlock(sock, 1);
		return (EINVAL);
	}
	if ((flags & ~(MSG_DONTWAIT)) != 0) {
		socket_unlock(sock, 1);
		return (ENOTSUP);
	}
check_again:
	if (((flags & MSG_DONTWAIT) != 0 || (sock->so_state & SS_NBIO) != 0) &&
	    sock->so_comp.tqh_first == NULL) {
		socket_unlock(sock, 1);
		return (EWOULDBLOCK);
	}

	if (sock->so_proto->pr_getlock != NULL)  {
		mutex_held = (*sock->so_proto->pr_getlock)(sock, PR_F_WILLUNLOCK);
		dosocklock = 1;
	} else {
		mutex_held = sock->so_proto->pr_domain->dom_mtx;
		dosocklock = 0;
	}

	while (TAILQ_EMPTY(&sock->so_comp) && sock->so_error == 0) {
		if (sock->so_state & SS_CANTRCVMORE) {
			sock->so_error = ECONNABORTED;
			break;
		}
		error = msleep((caddr_t)&sock->so_timeo, mutex_held,
		    PSOCK | PCATCH, "sock_accept", NULL);
		if (error != 0) {
			socket_unlock(sock, 1);
			return (error);
		}
	}
	if (sock->so_error != 0) {
		error = sock->so_error;
		sock->so_error = 0;
		socket_unlock(sock, 1);
		return (error);
	}

	so_acquire_accept_list(sock, NULL);
	if (TAILQ_EMPTY(&sock->so_comp)) {
		so_release_accept_list(sock);
		goto check_again;
	}
	new_so = TAILQ_FIRST(&sock->so_comp);
	TAILQ_REMOVE(&sock->so_comp, new_so, so_list);
	new_so->so_state &= ~SS_COMP;
	new_so->so_head = NULL;
	sock->so_qlen--;

	so_release_accept_list(sock);

	/*
	 * Count the accepted socket as an in-kernel socket
	 */
	new_so->so_flags1 |= SOF1_IN_KERNEL_SOCKET;
	INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_in_kernel_total);
	if (is_internal) {
		INC_ATOMIC_INT64_LIM(net_api_stats.nas_socket_in_kernel_os_total);
	}

	/*
	 * Pass the pre-accepted socket to any interested socket filter(s).
	 * Upon failure, the socket would have been closed by the callee.
	 */
	if (new_so->so_filt != NULL) {
		/*
		 * Temporarily drop the listening socket's lock before we
		 * hand off control over to the socket filter(s), but keep
		 * a reference so that it won't go away.  We'll grab it
		 * again once we're done with the filter(s).
		 */
		socket_unlock(sock, 0);
		if ((error = soacceptfilter(new_so, sock)) != 0) {
			/* Drop reference on listening socket */
			sodereference(sock);
			return (error);
		}
		socket_lock(sock, 0);
	}

	if (dosocklock)	{
		LCK_MTX_ASSERT(new_so->so_proto->pr_getlock(new_so, 0),
		    LCK_MTX_ASSERT_NOTOWNED);
		socket_lock(new_so, 1);
	}

	(void) soacceptlock(new_so, &sa, 0);

	socket_unlock(sock, 1);	/* release the head */

	/* see comments in sock_setupcall() */
	if (callback != NULL) {
#if CONFIG_EMBEDDED
		sock_setupcalls_locked(new_so, callback, cookie, callback, cookie, 0);
#else
		sock_setupcalls_locked(new_so, callback, cookie, NULL, NULL, 0);
#endif /* !CONFIG_EMBEDDED */
	}

	if (sa != NULL && from != NULL) {
		if (fromlen > sa->sa_len)
			fromlen = sa->sa_len;
		memcpy(from, sa, fromlen);
	}
	if (sa != NULL)
		FREE(sa, M_SONAME);

	/*
	 * If the socket has been marked as inactive by sosetdefunct(),
	 * disallow further operations on it.
	 */
	if (new_so->so_flags & SOF_DEFUNCT) {
		(void) sodefunct(current_proc(), new_so,
		    SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL);
	}
	*new_sock = new_so;
	if (dosocklock)
		socket_unlock(new_so, 1);
	return (error);
}