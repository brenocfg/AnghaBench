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
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct itimerval {int /*<<< orphan*/  it_interval; int /*<<< orphan*/  it_value; } ;
struct cpu_itimer {void* incr; void* expires; void* error; void* incr_error; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  void* cputime_t ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {struct cpu_itimer* it; } ;

/* Variables and functions */
 unsigned int CPUCLOCK_VIRT ; 
 int /*<<< orphan*/  ITIMER_PROF ; 
 int /*<<< orphan*/  ITIMER_VIRTUAL ; 
 void* cputime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_eq (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cputime_gt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_one_jiffy ; 
 void* cputime_sub_ns (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_timeval (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cputime_zero ; 
 int /*<<< orphan*/  set_process_cpu_timer (struct task_struct*,unsigned int,void**,void**) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 void* timeval_to_cputime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeval_to_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_itimer_state (int /*<<< orphan*/ ,struct itimerval const* const,void*) ; 

__attribute__((used)) static void set_cpu_itimer(struct task_struct *tsk, unsigned int clock_id,
			   const struct itimerval *const value,
			   struct itimerval *const ovalue)
{
	cputime_t cval, nval, cinterval, ninterval;
	s64 ns_ninterval, ns_nval;
	struct cpu_itimer *it = &tsk->signal->it[clock_id];

	nval = timeval_to_cputime(&value->it_value);
	ns_nval = timeval_to_ns(&value->it_value);
	ninterval = timeval_to_cputime(&value->it_interval);
	ns_ninterval = timeval_to_ns(&value->it_interval);

	it->incr_error = cputime_sub_ns(ninterval, ns_ninterval);
	it->error = cputime_sub_ns(nval, ns_nval);

	spin_lock_irq(&tsk->sighand->siglock);

	cval = it->expires;
	cinterval = it->incr;
	if (!cputime_eq(cval, cputime_zero) ||
	    !cputime_eq(nval, cputime_zero)) {
		if (cputime_gt(nval, cputime_zero))
			nval = cputime_add(nval, cputime_one_jiffy);
		set_process_cpu_timer(tsk, clock_id, &nval, &cval);
	}
	it->expires = nval;
	it->incr = ninterval;
	trace_itimer_state(clock_id == CPUCLOCK_VIRT ?
			   ITIMER_VIRTUAL : ITIMER_PROF, value, nval);

	spin_unlock_irq(&tsk->sighand->siglock);

	if (ovalue) {
		cputime_to_timeval(cval, &ovalue->it_value);
		cputime_to_timeval(cinterval, &ovalue->it_interval);
	}
}