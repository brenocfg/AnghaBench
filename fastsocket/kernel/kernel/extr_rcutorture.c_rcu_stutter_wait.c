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
 int /*<<< orphan*/  HZ ; 
 scalar_t__ rcutorture_runnable ; 
 int /*<<< orphan*/  rcutorture_shutdown_absorb (char*) ; 
 int round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ stutter_pause_test ; 

__attribute__((used)) static void
rcu_stutter_wait(char *title)
{
	while (stutter_pause_test || !rcutorture_runnable) {
		if (rcutorture_runnable)
			schedule_timeout_interruptible(1);
		else
			schedule_timeout_interruptible(round_jiffies_relative(HZ));
		rcutorture_shutdown_absorb(title);
	}
}