#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  VERBOSE_PRINTK_STRING (char*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  rcutorture_shutdown_absorb (char*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int stutter ; 
 int stutter_pause_test ; 

__attribute__((used)) static int
rcu_torture_stutter(void *arg)
{
	VERBOSE_PRINTK_STRING("rcu_torture_stutter task started");
	do {
		schedule_timeout_interruptible(stutter * HZ);
		stutter_pause_test = 1;
		if (!kthread_should_stop())
			schedule_timeout_interruptible(stutter * HZ);
		stutter_pause_test = 0;
		rcutorture_shutdown_absorb("rcu_torture_stutter");
	} while (!kthread_should_stop());
	VERBOSE_PRINTK_STRING("rcu_torture_stutter task stopping");
	return 0;
}