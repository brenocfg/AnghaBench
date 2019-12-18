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
struct task_struct {TYPE_1__* signal; } ;
struct cpu_itimer {scalar_t__ error; scalar_t__ incr_error; int /*<<< orphan*/  expires; int /*<<< orphan*/  incr; } ;
typedef  int /*<<< orphan*/  cputime_t ;
struct TYPE_2__ {int /*<<< orphan*/  leader_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_PROF ; 
 int /*<<< orphan*/  ITIMER_VIRTUAL ; 
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int SIGPROF ; 
 int /*<<< orphan*/  __group_send_sig_info (int,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_ge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_one_jiffy ; 
 int /*<<< orphan*/  cputime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_zero ; 
 scalar_t__ onecputick ; 
 int /*<<< orphan*/  trace_itimer_expire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_cpu_itimer(struct task_struct *tsk, struct cpu_itimer *it,
			     cputime_t *expires, cputime_t cur_time, int signo)
{
	if (cputime_eq(it->expires, cputime_zero))
		return;

	if (cputime_ge(cur_time, it->expires)) {
		if (!cputime_eq(it->incr, cputime_zero)) {
			it->expires = cputime_add(it->expires, it->incr);
			it->error += it->incr_error;
			if (it->error >= onecputick) {
				it->expires = cputime_sub(it->expires,
							  cputime_one_jiffy);
				it->error -= onecputick;
			}
		} else {
			it->expires = cputime_zero;
		}

		trace_itimer_expire(signo == SIGPROF ?
				    ITIMER_PROF : ITIMER_VIRTUAL,
				    tsk->signal->leader_pid, cur_time);
		__group_send_sig_info(signo, SEND_SIG_PRIV, tsk);
	}

	if (!cputime_eq(it->expires, cputime_zero) &&
	    (cputime_eq(*expires, cputime_zero) ||
	     cputime_lt(it->expires, *expires))) {
		*expires = it->expires;
	}
}