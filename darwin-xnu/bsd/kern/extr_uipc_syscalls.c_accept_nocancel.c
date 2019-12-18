#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_12__ {int /*<<< orphan*/ * tqh_first; } ;
struct socket {int so_options; int so_state; int so_error; int so_usecount; int so_flags; TYPE_2__ so_snd; TYPE_1__ so_rcv; int /*<<< orphan*/ * so_filt; int /*<<< orphan*/  so_qlen; int /*<<< orphan*/ * so_head; TYPE_5__ so_comp; int /*<<< orphan*/  so_timeo; TYPE_4__* so_proto; } ;
struct sockaddr {int sa_len; } ;
struct proc {int dummy; } ;
struct fileproc {short f_flag; struct sockaddr* f_data; int /*<<< orphan*/ * f_ops; } ;
struct accept_nocancel_args {int s; int /*<<< orphan*/  anamelen; int /*<<< orphan*/  name; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
typedef  struct sockaddr* caddr_t ;
struct TYPE_11__ {int pr_flags; TYPE_3__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int,...) ; 
 int /*<<< orphan*/  DBG_FUNC_START ; 
 int EBADF ; 
 void* ECONNABORTED ; 
 int EINVAL ; 
 int ENOTSOCK ; 
 scalar_t__ ENTR_SHOULDTRACE ; 
 int EOPNOTSUPP ; 
 int EWOULDBLOCK ; 
 int FASYNC ; 
 int FNONBLOCK ; 
 int /*<<< orphan*/  FREE (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_ENERGYTRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  M_SONAME ; 
 int PCATCH ; 
 int PR_CONNREQUIRED ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 int PSOCK ; 
 int /*<<< orphan*/  SB_ASYNC ; 
 int /*<<< orphan*/  SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL ; 
 int SOF_DEFUNCT ; 
 int SO_ACCEPTCONN ; 
 int SS_ASYNC ; 
 int SS_CANTRCVMORE ; 
 int SS_COMP ; 
 int SS_DRAINING ; 
 int SS_NBIO ; 
 int SS_NOFDREF ; 
 scalar_t__ TAILQ_EMPTY (TYPE_5__*) ; 
 struct socket* TAILQ_FIRST (TYPE_5__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_5__*,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct socket*) ; 
 int copyin (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int copyout (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int falloc (struct proc*,struct fileproc**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_drop (int) ; 
 int /*<<< orphan*/  fp_drop (struct proc*,int,struct fileproc*,int) ; 
 int fp_getfsock (struct proc*,int,struct fileproc**,struct socket**) ; 
 int /*<<< orphan*/  kEnTrActKernSocket ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  lck_mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mac_socket_check_accept (int /*<<< orphan*/ ,struct socket*) ; 
 int mac_socket_check_accepted (int /*<<< orphan*/ ,struct socket*) ; 
 int msleep (struct sockaddr*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct socket*,int) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  procfdtbl_releasefd (struct proc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_acquire_accept_list (struct socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_list ; 
 int /*<<< orphan*/  so_release_accept_list (struct socket*) ; 
 int soacceptfilter (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  soacceptlock (struct socket*,struct sockaddr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockaddr ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  socketops ; 
 int /*<<< orphan*/  soclose (struct socket*) ; 
 int /*<<< orphan*/  sodefunct (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sodereference (struct socket*) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_cwd (int /*<<< orphan*/ ) ; 

int
accept_nocancel(struct proc *p, struct accept_nocancel_args *uap,
    int32_t *retval)
{
	struct fileproc *fp;
	struct sockaddr *sa = NULL;
	socklen_t namelen;
	int error;
	struct socket *head, *so = NULL;
	lck_mtx_t *mutex_held;
	int fd = uap->s;
	int newfd;
	short fflag;		/* type must match fp->f_flag */
	int dosocklock = 0;

	*retval = -1;

	AUDIT_ARG(fd, uap->s);

	if (uap->name) {
		error = copyin(uap->anamelen, (caddr_t)&namelen,
		    sizeof (socklen_t));
		if (error)
			return (error);
	}
	error = fp_getfsock(p, fd, &fp, &head);
	if (error) {
		if (error == EOPNOTSUPP)
			error = ENOTSOCK;
		return (error);
	}
	if (head == NULL) {
		error = EBADF;
		goto out;
	}
#if CONFIG_MACF_SOCKET_SUBSET
	if ((error = mac_socket_check_accept(kauth_cred_get(), head)) != 0)
		goto out;
#endif /* MAC_SOCKET_SUBSET */

	socket_lock(head, 1);

	if (head->so_proto->pr_getlock != NULL)  {
		mutex_held = (*head->so_proto->pr_getlock)(head, PR_F_WILLUNLOCK);
		dosocklock = 1;
	} else {
		mutex_held = head->so_proto->pr_domain->dom_mtx;
		dosocklock = 0;
	}

	if ((head->so_options & SO_ACCEPTCONN) == 0) {
		if ((head->so_proto->pr_flags & PR_CONNREQUIRED) == 0) {
			error = EOPNOTSUPP;
		} else {
			/* POSIX: The socket is not accepting connections */
			error = EINVAL;
		}
		socket_unlock(head, 1);
		goto out;
	}
check_again:
	if ((head->so_state & SS_NBIO) && head->so_comp.tqh_first == NULL) {
		socket_unlock(head, 1);
		error = EWOULDBLOCK;
		goto out;
	}
	while (TAILQ_EMPTY(&head->so_comp) && head->so_error == 0) {
		if (head->so_state & SS_CANTRCVMORE) {
			head->so_error = ECONNABORTED;
			break;
		}
		if (head->so_usecount < 1)
			panic("accept: head=%p refcount=%d\n", head,
			    head->so_usecount);
		error = msleep((caddr_t)&head->so_timeo, mutex_held,
		    PSOCK | PCATCH, "accept", 0);
		if (head->so_usecount < 1)
			panic("accept: 2 head=%p refcount=%d\n", head,
			    head->so_usecount);
		if ((head->so_state & SS_DRAINING)) {
			error = ECONNABORTED;
		}
		if (error) {
			socket_unlock(head, 1);
			goto out;
		}
	}
	if (head->so_error) {
		error = head->so_error;
		head->so_error = 0;
		socket_unlock(head, 1);
		goto out;
	}

	/*
	 * At this point we know that there is at least one connection
	 * ready to be accepted. Remove it from the queue prior to
	 * allocating the file descriptor for it since falloc() may
	 * block allowing another process to accept the connection
	 * instead.
	 */
	lck_mtx_assert(mutex_held, LCK_MTX_ASSERT_OWNED);

	so_acquire_accept_list(head, NULL);
	if (TAILQ_EMPTY(&head->so_comp)) {
		so_release_accept_list(head);
		goto check_again;
	}

	so = TAILQ_FIRST(&head->so_comp);
	TAILQ_REMOVE(&head->so_comp, so, so_list);
	so->so_head = NULL;
	so->so_state &= ~SS_COMP;
	head->so_qlen--;
	so_release_accept_list(head);

	/* unlock head to avoid deadlock with select, keep a ref on head */
	socket_unlock(head, 0);

#if CONFIG_MACF_SOCKET_SUBSET
	/*
	 * Pass the pre-accepted socket to the MAC framework. This is
	 * cheaper than allocating a file descriptor for the socket,
	 * calling the protocol accept callback, and possibly freeing
	 * the file descriptor should the MAC check fails.
	 */
	if ((error = mac_socket_check_accepted(kauth_cred_get(), so)) != 0) {
		socket_lock(so, 1);
		so->so_state &= ~SS_NOFDREF;
		socket_unlock(so, 1);
		soclose(so);
		/* Drop reference on listening socket */
		sodereference(head);
		goto out;
	}
#endif /* MAC_SOCKET_SUBSET */

	/*
	 * Pass the pre-accepted socket to any interested socket filter(s).
	 * Upon failure, the socket would have been closed by the callee.
	 */
	if (so->so_filt != NULL && (error = soacceptfilter(so, head)) != 0) {
		/* Drop reference on listening socket */
		sodereference(head);
		/* Propagate socket filter's error code to the caller */
		goto out;
	}

	fflag = fp->f_flag;
	error = falloc(p, &fp, &newfd, vfs_context_current());
	if (error) {
		/*
		 * Probably ran out of file descriptors.
		 *
		 * <rdar://problem/8554930>
		 * Don't put this back on the socket like we used to, that
		 * just causes the client to spin. Drop the socket.
		 */
		socket_lock(so, 1);
		so->so_state &= ~SS_NOFDREF;
		socket_unlock(so, 1);
		soclose(so);
		sodereference(head);
		goto out;
	}
	*retval = newfd;
	fp->f_flag = fflag;
	fp->f_ops = &socketops;
	fp->f_data = (caddr_t)so;

	socket_lock(head, 0);
	if (dosocklock)
		socket_lock(so, 1);

	/* Sync socket non-blocking/async state with file flags */
	if (fp->f_flag & FNONBLOCK) {
		so->so_state |= SS_NBIO;
	} else {
		so->so_state &= ~SS_NBIO;
	}

	if (fp->f_flag & FASYNC) {
		so->so_state |= SS_ASYNC;
		so->so_rcv.sb_flags |= SB_ASYNC;
		so->so_snd.sb_flags |= SB_ASYNC;
	} else {
		so->so_state &= ~SS_ASYNC;
		so->so_rcv.sb_flags &= ~SB_ASYNC;
		so->so_snd.sb_flags &= ~SB_ASYNC;
	}

	(void) soacceptlock(so, &sa, 0);
	socket_unlock(head, 1);
	if (sa == NULL) {
		namelen = 0;
		if (uap->name)
			goto gotnoname;
		error = 0;
		goto releasefd;
	}
	AUDIT_ARG(sockaddr, vfs_context_cwd(vfs_context_current()), sa);

	if (uap->name) {
		socklen_t	sa_len;

		/* save sa_len before it is destroyed */
		sa_len = sa->sa_len;
		namelen = MIN(namelen, sa_len);
		error = copyout(sa, uap->name, namelen);
		if (!error)
			/* return the actual, untruncated address length */
			namelen = sa_len;
gotnoname:
		error = copyout((caddr_t)&namelen, uap->anamelen,
		    sizeof (socklen_t));
	}
	FREE(sa, M_SONAME);

releasefd:
	/*
	 * If the socket has been marked as inactive by sosetdefunct(),
	 * disallow further operations on it.
	 */
	if (so->so_flags & SOF_DEFUNCT) {
		sodefunct(current_proc(), so,
		    SHUTDOWN_SOCKET_LEVEL_DISCONNECT_INTERNAL);
	}

	if (dosocklock)
		socket_unlock(so, 1);

	proc_fdlock(p);
	procfdtbl_releasefd(p, newfd, NULL);
	fp_drop(p, newfd, fp, 1);
	proc_fdunlock(p);

out:
	file_drop(fd);

	if (error == 0 && ENTR_SHOULDTRACE) {
		KERNEL_ENERGYTRACE(kEnTrActKernSocket, DBG_FUNC_START,
		    newfd, 0, (int64_t)VM_KERNEL_ADDRPERM(so));
	}
	return (error);
}