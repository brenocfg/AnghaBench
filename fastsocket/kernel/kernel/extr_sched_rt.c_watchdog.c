#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sum_exec_runtime; } ;
struct TYPE_7__ {int /*<<< orphan*/  sched_exp; } ;
struct TYPE_6__ {unsigned long timeout; } ;
struct task_struct {TYPE_3__ se; TYPE_2__ cputime_expires; TYPE_1__ rt; TYPE_4__* signal; } ;
struct rq {int dummy; } ;
struct TYPE_10__ {unsigned long rlim_cur; unsigned long rlim_max; } ;
struct TYPE_9__ {TYPE_5__* rlim; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int HZ ; 
 size_t RLIMIT_RTTIME ; 
 unsigned long RLIM_INFINITY ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  min (unsigned long,unsigned long) ; 

__attribute__((used)) static void watchdog(struct rq *rq, struct task_struct *p)
{
	unsigned long soft, hard;

	if (!p->signal)
		return;

	soft = p->signal->rlim[RLIMIT_RTTIME].rlim_cur;
	hard = p->signal->rlim[RLIMIT_RTTIME].rlim_max;

	if (soft != RLIM_INFINITY) {
		unsigned long next;

		p->rt.timeout++;
		next = DIV_ROUND_UP(min(soft, hard), USEC_PER_SEC/HZ);
		if (p->rt.timeout > next)
			p->cputime_expires.sched_exp = p->se.sum_exec_runtime;
	}
}