#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int so_flags; TYPE_3__* so_proto; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_6__ {TYPE_2__* pr_usrreqs; TYPE_1__* pr_domain; int /*<<< orphan*/ * (* pr_getlock ) (struct socket*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int (* pru_abort ) (struct socket*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * dom_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int SOF_ABORTED ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int /*<<< orphan*/ * stub1 (struct socket*,int /*<<< orphan*/ ) ; 
 int stub2 (struct socket*) ; 

int
soabort(struct socket *so)
{
	int error;

#ifdef MORE_LOCKING_DEBUG
	lck_mtx_t *mutex_held;

	if (so->so_proto->pr_getlock != NULL)
		mutex_held = (*so->so_proto->pr_getlock)(so, 0);
	else
		mutex_held = so->so_proto->pr_domain->dom_mtx;
	LCK_MTX_ASSERT(mutex_held, LCK_MTX_ASSERT_OWNED);
#endif

	if ((so->so_flags & SOF_ABORTED) == 0) {
		so->so_flags |= SOF_ABORTED;
		error = (*so->so_proto->pr_usrreqs->pru_abort)(so);
		if (error) {
			sofree(so);
			return (error);
		}
	}
	return (0);
}