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
struct pfioc_tm {size_t timeout; int seconds; } ;
struct TYPE_2__ {int* timeout; } ;

/* Variables and functions */
#define  DIOCGETTIMEOUT 129 
#define  DIOCSETTIMEOUT 128 
 int EINVAL ; 
 size_t PFTM_INTERVAL ; 
 size_t PFTM_MAX ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 TYPE_1__ pf_default_rule ; 
 int /*<<< orphan*/  pf_purge_thread_fn ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfioctl_ioc_tm(u_long cmd, struct pfioc_tm *pt, struct proc *p)
{
#pragma unused(p)
	int error = 0;

	switch (cmd) {
	case DIOCSETTIMEOUT: {
		int old;

		if (pt->timeout < 0 || pt->timeout >= PFTM_MAX ||
		    pt->seconds < 0) {
			error = EINVAL;
			goto fail;
		}
		old = pf_default_rule.timeout[pt->timeout];
		if (pt->timeout == PFTM_INTERVAL && pt->seconds == 0)
			pt->seconds = 1;
		pf_default_rule.timeout[pt->timeout] = pt->seconds;
		if (pt->timeout == PFTM_INTERVAL && pt->seconds < old)
			wakeup(pf_purge_thread_fn);
		pt->seconds = old;
		break;
	}

	case DIOCGETTIMEOUT: {
		if (pt->timeout < 0 || pt->timeout >= PFTM_MAX) {
			error = EINVAL;
			goto fail;
		}
		pt->seconds = pf_default_rule.timeout[pt->timeout];
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}
fail:
	return (error);
}