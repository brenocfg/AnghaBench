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
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_RCU_RANDOM (int /*<<< orphan*/ ) ; 
 scalar_t__ FULLSTOP_DONTSTOP ; 
 int /*<<< orphan*/  VERBOSE_PRINTK_STRING (char*) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fullstop ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  rand ; 
 int rcu_random (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_stutter_wait (char*) ; 
 int /*<<< orphan*/  rcutorture_shutdown_absorb (char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
rcu_torture_fakewriter(void *arg)
{
	DEFINE_RCU_RANDOM(rand);

	VERBOSE_PRINTK_STRING("rcu_torture_fakewriter task started");
	set_user_nice(current, 19);

	do {
		schedule_timeout_uninterruptible(1 + rcu_random(&rand)%10);
		udelay(rcu_random(&rand) & 0x3ff);
		cur_ops->sync();
		rcu_stutter_wait("rcu_torture_fakewriter");
	} while (!kthread_should_stop() && fullstop == FULLSTOP_DONTSTOP);

	VERBOSE_PRINTK_STRING("rcu_torture_fakewriter task stopping");
	rcutorture_shutdown_absorb("rcu_torture_fakewriter");
	while (!kthread_should_stop())
		schedule_timeout_uninterruptible(1);
	return 0;
}