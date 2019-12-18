#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct sockbuf {int sb_flags; int /*<<< orphan*/ * sb_mb; int /*<<< orphan*/  sb_sel; int /*<<< orphan*/ * sb_upcallarg; int /*<<< orphan*/ * sb_upcall; TYPE_1__ sb_timeo; int /*<<< orphan*/ * sb_lastrecord; int /*<<< orphan*/ * sb_mbtail; scalar_t__ sb_lowat; scalar_t__ sb_ctl; scalar_t__ sb_mbmax; scalar_t__ sb_mbcnt; scalar_t__ sb_hiwat; scalar_t__ sb_cc; int /*<<< orphan*/  sb_so; } ;
struct socket {struct protosw* so_proto; struct sockbuf so_rcv; } ;
struct protosw {int pr_flags; TYPE_2__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  asb ;
struct TYPE_4__ {int /*<<< orphan*/  (* dom_dispose ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PR_RIGHTS ; 
 int SBL_IGNDEFUNCT ; 
 int SBL_NOINTR ; 
 int SBL_WAIT ; 
 int SB_DROP ; 
 int SB_KNOTE ; 
 int SB_LOCK ; 
 int SB_SEL ; 
 int SB_UPCALL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct sockbuf*,int) ; 
 int /*<<< orphan*/  sblock (struct sockbuf*,int) ; 
 int /*<<< orphan*/  sbrelease (struct sockbuf*) ; 
 int /*<<< orphan*/  sbunlock (struct sockbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selthreadclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sflt_notify (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socantrcvmore (struct socket*) ; 
 int /*<<< orphan*/  sock_evt_flush_read ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void
sorflush(struct socket *so)
{
	struct sockbuf *sb = &so->so_rcv;
	struct protosw *pr = so->so_proto;
	struct sockbuf asb;
#ifdef notyet
	lck_mtx_t *mutex_held;
	/*
	 * XXX: This code is currently commented out, because we may get here
	 * as part of sofreelastref(), and at that time, pr_getlock() may no
	 * longer be able to return us the lock; this will be fixed in future.
	 */
	if (so->so_proto->pr_getlock != NULL)
		mutex_held = (*so->so_proto->pr_getlock)(so, 0);
	else
		mutex_held = so->so_proto->pr_domain->dom_mtx;

	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);
#endif /* notyet */

	sflt_notify(so, sock_evt_flush_read, NULL);

	socantrcvmore(so);

	/*
	 * Obtain lock on the socket buffer (SB_LOCK).  This is required
	 * to prevent the socket buffer from being unexpectedly altered
	 * while it is used by another thread in socket send/receive.
	 *
	 * sblock() must not fail here, hence the assertion.
	 */
	(void) sblock(sb, SBL_WAIT | SBL_NOINTR | SBL_IGNDEFUNCT);
	VERIFY(sb->sb_flags & SB_LOCK);

	/*
	 * Copy only the relevant fields from "sb" to "asb" which we
	 * need for sbrelease() to function.  In particular, skip
	 * sb_sel as it contains the wait queue linkage, which would
	 * wreak havoc if we were to issue selthreadclear() on "asb".
	 * Make sure to not carry over SB_LOCK in "asb", as we need
	 * to acquire it later as part of sbrelease().
	 */
	bzero(&asb, sizeof (asb));
	asb.sb_cc		= sb->sb_cc;
	asb.sb_hiwat		= sb->sb_hiwat;
	asb.sb_mbcnt		= sb->sb_mbcnt;
	asb.sb_mbmax		= sb->sb_mbmax;
	asb.sb_ctl		= sb->sb_ctl;
	asb.sb_lowat		= sb->sb_lowat;
	asb.sb_mb		= sb->sb_mb;
	asb.sb_mbtail		= sb->sb_mbtail;
	asb.sb_lastrecord	= sb->sb_lastrecord;
	asb.sb_so		= sb->sb_so;
	asb.sb_flags		= sb->sb_flags;
	asb.sb_flags		&= ~(SB_LOCK|SB_SEL|SB_KNOTE|SB_UPCALL);
	asb.sb_flags		|= SB_DROP;

	/*
	 * Ideally we'd bzero() these and preserve the ones we need;
	 * but to do that we'd need to shuffle things around in the
	 * sockbuf, and we can't do it now because there are KEXTS
	 * that are directly referring to the socket structure.
	 *
	 * Setting SB_DROP acts as a barrier to prevent further appends.
	 * Clearing SB_SEL is done for selthreadclear() below.
	 */
	sb->sb_cc		= 0;
	sb->sb_hiwat		= 0;
	sb->sb_mbcnt		= 0;
	sb->sb_mbmax		= 0;
	sb->sb_ctl		= 0;
	sb->sb_lowat		= 0;
	sb->sb_mb		= NULL;
	sb->sb_mbtail		= NULL;
	sb->sb_lastrecord	= NULL;
	sb->sb_timeo.tv_sec	= 0;
	sb->sb_timeo.tv_usec	= 0;
	sb->sb_upcall		= NULL;
	sb->sb_upcallarg	= NULL;
	sb->sb_flags		&= ~(SB_SEL|SB_UPCALL);
	sb->sb_flags		|= SB_DROP;

	sbunlock(sb, TRUE);	/* keep socket locked */

	/*
	 * Note that selthreadclear() is called on the original "sb" and
	 * not the local "asb" because of the way wait queue linkage is
	 * implemented.  Given that selwakeup() may be triggered, SB_SEL
	 * should no longer be set (cleared above.)
	 */
	selthreadclear(&sb->sb_sel);

	if ((pr->pr_flags & PR_RIGHTS) && pr->pr_domain->dom_dispose)
		(*pr->pr_domain->dom_dispose)(asb.sb_mb);

	sbrelease(&asb);
}