#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct proc {int dummy; } ;
struct pfioc_limit {size_t index; int limit; } ;
struct TYPE_2__ {int limit; int /*<<< orphan*/ * pp; } ;

/* Variables and functions */
#define  DIOCGETLIMIT 129 
#define  DIOCSETLIMIT 128 
 int EINVAL ; 
 size_t PF_LIMIT_MAX ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 TYPE_1__* pf_pool_limits ; 
 int /*<<< orphan*/  pool_sethardlimit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfioctl_ioc_limit(u_long cmd, struct pfioc_limit *pl, struct proc *p)
{
#pragma unused(p)
	int error = 0;

	switch (cmd) {
	case DIOCGETLIMIT: {

		if (pl->index < 0 || pl->index >= PF_LIMIT_MAX) {
			error = EINVAL;
			goto fail;
		}
		pl->limit = pf_pool_limits[pl->index].limit;
		break;
	}

	case DIOCSETLIMIT: {
		int old_limit;

		if (pl->index < 0 || pl->index >= PF_LIMIT_MAX ||
		    pf_pool_limits[pl->index].pp == NULL) {
			error = EINVAL;
			goto fail;
		}
		pool_sethardlimit(pf_pool_limits[pl->index].pp,
		    pl->limit, NULL, 0);
		old_limit = pf_pool_limits[pl->index].limit;
		pf_pool_limits[pl->index].limit = pl->limit;
		pl->limit = old_limit;
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
fail:
	return (error);
}