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
struct TYPE_8__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  sb_flags; } ;
struct socket {int so_flags; int /*<<< orphan*/  so_upcallusecount; TYPE_4__ so_snd; TYPE_3__ so_rcv; TYPE_2__* so_proto; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {TYPE_1__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  PR_F_WILLUNLOCK ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  SB_UPCALL ; 
 int SOF_CLOSEWAIT ; 
 int SOF_UPCALLCLOSEWAIT ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 

void
soclose_wait_locked(struct socket *so)
{
	lck_mtx_t *mutex_held;

	if (so->so_proto->pr_getlock != NULL)
		mutex_held = (*so->so_proto->pr_getlock)(so, PR_F_WILLUNLOCK);
	else
		mutex_held = so->so_proto->pr_domain->dom_mtx;
	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);

	/*
	 * Double check here and return if there's no outstanding upcall;
	 * otherwise proceed further only if SOF_UPCALLCLOSEWAIT is set.
	 */
	if (!so->so_upcallusecount || !(so->so_flags & SOF_UPCALLCLOSEWAIT))
		return;
	so->so_rcv.sb_flags &= ~SB_UPCALL;
	so->so_snd.sb_flags &= ~SB_UPCALL;
	so->so_flags |= SOF_CLOSEWAIT;

	(void) msleep((caddr_t)&so->so_upcallusecount, mutex_held, (PZERO - 1),
	    "soclose_wait_locked", NULL);
	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);
	so->so_flags &= ~SOF_CLOSEWAIT;
}