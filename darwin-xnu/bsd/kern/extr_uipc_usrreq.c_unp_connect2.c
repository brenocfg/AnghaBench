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
struct unpcb {int unp_flags; int /*<<< orphan*/  unp_mtx; struct unpcb* unp_conn; int /*<<< orphan*/  unp_peercred; int /*<<< orphan*/  unp_refs; } ;
struct socket {int so_type; scalar_t__ so_usecount; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct unpcb*,int /*<<< orphan*/ ) ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 int UNP_HAVEPC ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  cru2x (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 struct unpcb* sotounpcb (struct socket*) ; 
 int /*<<< orphan*/  unp_get_locks_in_order (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  unp_reflink ; 

int
unp_connect2(struct socket *so, struct socket *so2)
{
	struct unpcb *unp = sotounpcb(so);
	struct unpcb *unp2;

	if (so2->so_type != so->so_type)
		return (EPROTOTYPE);

	unp2 = sotounpcb(so2);

	LCK_MTX_ASSERT(&unp->unp_mtx, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&unp2->unp_mtx, LCK_MTX_ASSERT_OWNED);

	/* Verify both sockets are still opened */
	if (unp == 0 || unp2 == 0)
		return (EINVAL);

	unp->unp_conn = unp2;
	so2->so_usecount++;

	switch (so->so_type) {

	case SOCK_DGRAM:
		LIST_INSERT_HEAD(&unp2->unp_refs, unp, unp_reflink);

		if (so != so2) {
			/* Avoid lock order reversals due to drop/acquire in soisconnected. */
 			/* Keep an extra reference on so2 that will be dropped
			 * soon after getting the locks in order
			 */
			socket_unlock(so2, 0);
			soisconnected(so);
			unp_get_locks_in_order(so, so2);
			VERIFY(so2->so_usecount > 0);
			so2->so_usecount--;
		} else {
			soisconnected(so);
		}

		break;

	case SOCK_STREAM:
		/* This takes care of socketpair */
		if (!(unp->unp_flags & UNP_HAVEPC) &&
		    !(unp2->unp_flags & UNP_HAVEPC)) {
			cru2x(kauth_cred_get(), &unp->unp_peercred);
			unp->unp_flags |= UNP_HAVEPC;

			cru2x(kauth_cred_get(), &unp2->unp_peercred);
			unp2->unp_flags |= UNP_HAVEPC;
		}
		unp2->unp_conn = unp;
		so->so_usecount++;

		/* Avoid lock order reversals due to drop/acquire in soisconnected. */
		socket_unlock(so, 0);
		soisconnected(so2);

		/* Keep an extra reference on so2, that will be dropped soon after
		 * getting the locks in order again.
		 */
		socket_unlock(so2, 0);

		socket_lock(so, 0);
		soisconnected(so);

		unp_get_locks_in_order(so, so2);
		/* Decrement the extra reference left before */
		VERIFY(so2->so_usecount > 0);
		so2->so_usecount--;
		break;

	default:
		panic("unknown socket type %d in unp_connect2", so->so_type);
	}
	LCK_MTX_ASSERT(&unp->unp_mtx, LCK_MTX_ASSERT_OWNED);
	LCK_MTX_ASSERT(&unp2->unp_mtx, LCK_MTX_ASSERT_OWNED);
	return (0);
}