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
struct timer_list {int dummy; } ;
struct rcu_torture {scalar_t__ rtort_mbtest; int rtort_pipe_count; } ;
struct TYPE_2__ {int (* readlock ) () ;int (* completed ) () ;scalar_t__ irq_capable; int /*<<< orphan*/  (* readunlock ) (int) ;int /*<<< orphan*/  (* read_delay ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_RCU_RANDOM (int /*<<< orphan*/ ) ; 
 scalar_t__ FULLSTOP_DONTSTOP ; 
 int /*<<< orphan*/  HZ ; 
 int RCU_TORTURE_PIPE_LEN ; 
 int /*<<< orphan*/  VERBOSE_PRINTK_STRING (char*) ; 
 int /*<<< orphan*/ * __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (struct timer_list*) ; 
 scalar_t__ fullstop ; 
 scalar_t__ irqreader ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,int) ; 
 int /*<<< orphan*/  n_rcu_torture_mberror ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  rand ; 
 struct rcu_torture* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_stutter_wait (char*) ; 
 int /*<<< orphan*/  rcu_torture_batch ; 
 int /*<<< orphan*/  rcu_torture_count ; 
 int /*<<< orphan*/  rcu_torture_current ; 
 int /*<<< orphan*/  rcu_torture_timer ; 
 int /*<<< orphan*/  rcutorture_shutdown_absorb (char*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_timer_on_stack (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int stub5 () ; 
 int /*<<< orphan*/  stub6 (int) ; 
 int /*<<< orphan*/  timer_pending (struct timer_list*) ; 

__attribute__((used)) static int
rcu_torture_reader(void *arg)
{
	int completed;
	int idx;
	DEFINE_RCU_RANDOM(rand);
	struct rcu_torture *p;
	int pipe_count;
	struct timer_list t;

	VERBOSE_PRINTK_STRING("rcu_torture_reader task started");
	set_user_nice(current, 19);
	if (irqreader && cur_ops->irq_capable)
		setup_timer_on_stack(&t, rcu_torture_timer, 0);

	do {
		if (irqreader && cur_ops->irq_capable) {
			if (!timer_pending(&t))
				mod_timer(&t, 1);
		}
		idx = cur_ops->readlock();
		completed = cur_ops->completed();
		p = rcu_dereference(rcu_torture_current);
		if (p == NULL) {
			/* Wait for rcu_torture_writer to get underway */
			cur_ops->readunlock(idx);
			schedule_timeout_interruptible(HZ);
			continue;
		}
		if (p->rtort_mbtest == 0)
			atomic_inc(&n_rcu_torture_mberror);
		cur_ops->read_delay(&rand);
		preempt_disable();
		pipe_count = p->rtort_pipe_count;
		if (pipe_count > RCU_TORTURE_PIPE_LEN) {
			/* Should not happen, but... */
			pipe_count = RCU_TORTURE_PIPE_LEN;
		}
		++__get_cpu_var(rcu_torture_count)[pipe_count];
		completed = cur_ops->completed() - completed;
		if (completed > RCU_TORTURE_PIPE_LEN) {
			/* Should not happen, but... */
			completed = RCU_TORTURE_PIPE_LEN;
		}
		++__get_cpu_var(rcu_torture_batch)[completed];
		preempt_enable();
		cur_ops->readunlock(idx);
		schedule();
		rcu_stutter_wait("rcu_torture_reader");
	} while (!kthread_should_stop() && fullstop == FULLSTOP_DONTSTOP);
	VERBOSE_PRINTK_STRING("rcu_torture_reader task stopping");
	rcutorture_shutdown_absorb("rcu_torture_reader");
	if (irqreader && cur_ops->irq_capable)
		del_timer_sync(&t);
	while (!kthread_should_stop())
		schedule_timeout_uninterruptible(1);
	return 0;
}