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
struct socket {int so_flags; TYPE_2__* so_proto; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_abort ) (struct socket*) ;} ;

/* Variables and functions */
 int SOF_ABORTED ; 
 int /*<<< orphan*/  sofree (struct socket*) ; 
 int stub1 (struct socket*) ; 

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