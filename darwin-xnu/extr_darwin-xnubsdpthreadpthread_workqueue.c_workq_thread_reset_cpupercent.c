#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* workq_threadreq_t ;
struct TYPE_7__ {int trp_flags; scalar_t__ trp_refillms; int /*<<< orphan*/  trp_cpupercent; } ;
typedef  TYPE_2__ workq_threadreq_param_t ;
typedef  int uint64_t ;
struct uthread {int uu_workq_flags; } ;
struct TYPE_6__ {int tr_flags; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  THREAD_CPULIMIT_BLOCK ; 
 int /*<<< orphan*/  THREAD_CPULIMIT_DISABLE ; 
 int TRP_CPUPERCENT ; 
 int TR_FLAG_WL_PARAMS ; 
 int UT_WORKQ_CPUPERCENT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct uthread* current_uthread () ; 
 TYPE_2__ kqueue_threadreq_workloop_param (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_set_cpulimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
workq_thread_reset_cpupercent(workq_threadreq_t req, struct uthread *uth)
{
	assert(uth == current_uthread());
	workq_threadreq_param_t trp = { };

	if (req && (req->tr_flags & TR_FLAG_WL_PARAMS)) {
		trp = kqueue_threadreq_workloop_param(req);
	}

	if (uth->uu_workq_flags & UT_WORKQ_CPUPERCENT) {
		/*
		 * Going through disable when we have an existing CPU percent limit
		 * set will force the ledger to refill the token bucket of the current
		 * thread. Removing any penalty applied by previous thread use.
		 */
		thread_set_cpulimit(THREAD_CPULIMIT_DISABLE, 0, 0);
		uth->uu_workq_flags &= ~UT_WORKQ_CPUPERCENT;
	}

	if (trp.trp_flags & TRP_CPUPERCENT) {
		thread_set_cpulimit(THREAD_CPULIMIT_BLOCK, trp.trp_cpupercent,
				(uint64_t)trp.trp_refillms * NSEC_PER_SEC);
		uth->uu_workq_flags |= UT_WORKQ_CPUPERCENT;
	}
}