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
struct rcu_torture {int rtort_pipe_count; int rtort_mbtest; } ;
struct TYPE_2__ {long (* completed ) () ;int /*<<< orphan*/  (* deferred_free ) (struct rcu_torture*) ;} ;
typedef  int /*<<< orphan*/  DEFINE_RCU_RANDOM ;

/* Variables and functions */
 scalar_t__ FULLSTOP_DONTSTOP ; 
 int RCU_TORTURE_PIPE_LEN ; 
 int /*<<< orphan*/  VERBOSE_PRINTK_STRING (char*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fullstop ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct rcu_torture*,struct rcu_torture*) ; 
 long rcu_batches_completed () ; 
 int rcu_random (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_stutter_wait (char*) ; 
 struct rcu_torture* rcu_torture_alloc () ; 
 struct rcu_torture* rcu_torture_current ; 
 int /*<<< orphan*/  rcu_torture_current_version ; 
 int /*<<< orphan*/ * rcu_torture_wcount ; 
 int /*<<< orphan*/  rcutorture_shutdown_absorb (char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  stub1 (struct rcu_torture*) ; 
 long stub2 () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rcu_torture_writer(void *arg)
{
	int i;
	long oldbatch = rcu_batches_completed();
	struct rcu_torture *rp;
	struct rcu_torture *old_rp;
	static DEFINE_RCU_RANDOM(rand);

	VERBOSE_PRINTK_STRING("rcu_torture_writer task started");
	set_user_nice(current, 19);

	do {
		schedule_timeout_uninterruptible(1);
		rp = rcu_torture_alloc();
		if (rp == NULL)
			continue;
		rp->rtort_pipe_count = 0;
		udelay(rcu_random(&rand) & 0x3ff);
		old_rp = rcu_torture_current;
		rp->rtort_mbtest = 1;
		rcu_assign_pointer(rcu_torture_current, rp);
		smp_wmb(); /* Mods to old_rp must follow rcu_assign_pointer() */
		if (old_rp) {
			i = old_rp->rtort_pipe_count;
			if (i > RCU_TORTURE_PIPE_LEN)
				i = RCU_TORTURE_PIPE_LEN;
			atomic_inc(&rcu_torture_wcount[i]);
			old_rp->rtort_pipe_count++;
			cur_ops->deferred_free(old_rp);
		}
		rcu_torture_current_version++;
		oldbatch = cur_ops->completed();
		rcu_stutter_wait("rcu_torture_writer");
	} while (!kthread_should_stop() && fullstop == FULLSTOP_DONTSTOP);
	VERBOSE_PRINTK_STRING("rcu_torture_writer task stopping");
	rcutorture_shutdown_absorb("rcu_torture_writer");
	while (!kthread_should_stop())
		schedule_timeout_uninterruptible(1);
	return 0;
}