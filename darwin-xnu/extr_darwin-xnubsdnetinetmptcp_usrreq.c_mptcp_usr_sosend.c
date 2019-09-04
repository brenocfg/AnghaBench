#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_ssize_t ;
struct uio {int dummy; } ;
struct socket {scalar_t__ so_type; int so_flags; int /*<<< orphan*/  so_snd; TYPE_4__* so_proto; } ;
struct sockaddr {int dummy; } ;
struct proc {TYPE_2__* p_stats; } ;
struct mbuf {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {TYPE_3__* pr_usrreqs; } ;
struct TYPE_7__ {int (* pru_send ) (struct socket*,int,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ru_msgsnd; } ;
struct TYPE_6__ {TYPE_1__ p_ru; } ;

/* Variables and functions */
 int EINVAL ; 
 int EJUSTRETURN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FALSE ; 
 int MSG_DONTROUTE ; 
 int MSG_EOR ; 
 int MSG_FLUSH ; 
 int MSG_HOLD ; 
 int MSG_OOB ; 
 int MSG_SEND ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OSIncrementAtomicLong (int /*<<< orphan*/ *) ; 
 int PRUS_MORETOCOME ; 
 scalar_t__ SOCK_STREAM ; 
 int SOF_ENABLE_MSGS ; 
 int SOF_MP_SUBFLOW ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mptcp_uiotombuf (struct uio*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct mbuf**) ; 
 scalar_t__ sbspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbunlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sflt_data_out (struct socket*,int /*<<< orphan*/ *,struct mbuf**,struct mbuf**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so_update_last_owner_locked (struct socket*,struct proc*) ; 
 int /*<<< orphan*/  so_update_policy (struct socket*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int /*<<< orphan*/  soclearfastopen (struct socket*) ; 
 int sosendcheck (struct socket*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int stub1 (struct socket*,int,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc*) ; 
 scalar_t__ uio_resid (struct uio*) ; 

__attribute__((used)) static int
mptcp_usr_sosend(struct socket *mp_so, struct sockaddr *addr, struct uio *uio,
    struct mbuf *top, struct mbuf *control, int flags)
{
#pragma unused(addr)
	int32_t space;
	user_ssize_t resid;
	int error, sendflags;
	struct proc *p = current_proc();
	int sblocked = 0;

	/* UIO is required for now, due to per-mbuf M_PKTHDR constrains */
	if (uio == NULL || top != NULL) {
		error = EINVAL;
		goto out;
	}
	resid = uio_resid(uio);

	socket_lock(mp_so, 1);
	so_update_last_owner_locked(mp_so, p);
	so_update_policy(mp_so);

	VERIFY(mp_so->so_type == SOCK_STREAM);
	VERIFY(!(mp_so->so_flags & SOF_MP_SUBFLOW));

	if ((flags & (MSG_OOB|MSG_DONTROUTE|MSG_HOLD|MSG_SEND|MSG_FLUSH)) ||
	    (mp_so->so_flags & SOF_ENABLE_MSGS)) {
		error = EOPNOTSUPP;
		socket_unlock(mp_so, 1);
		goto out;
	}

	/*
	 * In theory resid should be unsigned.  However, space must be
	 * signed, as it might be less than 0 if we over-committed, and we
	 * must use a signed comparison of space and resid.  On the other
	 * hand, a negative resid causes us to loop sending 0-length
	 * segments to the protocol.
	 */
	if (resid < 0 || (flags & MSG_EOR) || control != NULL) {
		error = EINVAL;
		socket_unlock(mp_so, 1);
		goto out;
	}

	OSIncrementAtomicLong(&p->p_stats->p_ru.ru_msgsnd);

	do {
		error = sosendcheck(mp_so, NULL, resid, 0, 0, flags,
		    &sblocked, NULL);
		if (error != 0)
			goto release;

		space = sbspace(&mp_so->so_snd);
		do {
			socket_unlock(mp_so, 0);
			/*
			 * Copy the data from userland into an mbuf chain.
			 */
			error = mptcp_uiotombuf(uio, M_WAITOK, space, 0, &top);
			if (error != 0) {
				socket_lock(mp_so, 0);
				goto release;
			}
			VERIFY(top != NULL);
			space -= resid - uio_resid(uio);
			resid = uio_resid(uio);
			socket_lock(mp_so, 0);

			/*
			 * Compute flags here, for pru_send and NKEs.
			 */
			sendflags = (resid > 0 && space > 0) ?
			    PRUS_MORETOCOME : 0;

			/*
			 * Socket filter processing
			 */
			VERIFY(control == NULL);
			error = sflt_data_out(mp_so, NULL, &top, &control, 0);
			if (error != 0) {
				if (error == EJUSTRETURN) {
					error = 0;
					top = NULL;
					/* always free control if any */
				}
				goto release;
			}
			if (control != NULL) {
				m_freem(control);
				control = NULL;
			}

			/*
			 * Pass data to protocol.
			 */
			error = (*mp_so->so_proto->pr_usrreqs->pru_send)
			    (mp_so, sendflags, top, NULL, NULL, p);

			top = NULL;
			if (error != 0)
				goto release;
		} while (resid != 0 && space > 0);
	} while (resid != 0);

release:
	if (sblocked)
		sbunlock(&mp_so->so_snd, FALSE); /* will unlock socket */
	else
		socket_unlock(mp_so, 1);
out:
	if (top != NULL)
		m_freem(top);
	if (control != NULL)
		m_freem(control);

	soclearfastopen(mp_so);

	return (error);
}