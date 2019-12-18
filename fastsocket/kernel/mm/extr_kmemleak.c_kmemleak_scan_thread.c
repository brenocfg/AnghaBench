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
 int /*<<< orphan*/  SECS_FIRST_SCAN ; 
 int /*<<< orphan*/  current ; 
 long jiffies_scan_wait ; 
 int /*<<< orphan*/  kmemleak_scan () ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  scan_mutex ; 
 long schedule_timeout_interruptible (long) ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kmemleak_scan_thread(void *arg)
{
	static int first_run = 1;

	pr_info("Automatic memory scanning thread started\n");
	set_user_nice(current, 10);

	/*
	 * Wait before the first scan to allow the system to fully initialize.
	 */
	if (first_run) {
		first_run = 0;
		ssleep(SECS_FIRST_SCAN);
	}

	while (!kthread_should_stop()) {
		signed long timeout = jiffies_scan_wait;

		mutex_lock(&scan_mutex);
		kmemleak_scan();
		mutex_unlock(&scan_mutex);

		/* wait before the next scan */
		while (timeout && !kthread_should_stop())
			timeout = schedule_timeout_interruptible(timeout);
	}

	pr_info("Automatic memory scanning thread ended\n");

	return 0;
}