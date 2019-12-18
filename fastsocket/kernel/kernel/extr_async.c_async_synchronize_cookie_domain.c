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
struct async_domain {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  scalar_t__ async_cookie_t ;

/* Variables and functions */
 scalar_t__ SYSTEM_BOOTING ; 
 int /*<<< orphan*/  async_done ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ initcall_debug ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ lowest_in_progress (struct async_domain*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void async_synchronize_cookie_domain(async_cookie_t cookie, struct async_domain *running)
{
	ktime_t starttime, delta, endtime;

	if (!running)
		return;

	if (initcall_debug && system_state == SYSTEM_BOOTING) {
		printk("async_waiting @ %i\n", task_pid_nr(current));
		starttime = ktime_get();
	}

	wait_event(async_done, lowest_in_progress(running) >= cookie);

	if (initcall_debug && system_state == SYSTEM_BOOTING) {
		endtime = ktime_get();
		delta = ktime_sub(endtime, starttime);

		printk("async_continuing @ %i after %lli usec\n",
			task_pid_nr(current),
			(long long)ktime_to_ns(delta) >> 10);
	}
}