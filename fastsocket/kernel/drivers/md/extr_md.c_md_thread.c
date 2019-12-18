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
struct md_thread {int /*<<< orphan*/  (* run ) (struct md_thread*) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  timeout; int /*<<< orphan*/  wqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  THREAD_WAKEUP ; 
 int /*<<< orphan*/  allow_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct md_thread*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int md_thread(void * arg)
{
	struct md_thread *thread = arg;

	/*
	 * md_thread is a 'system-thread', it's priority should be very
	 * high. We avoid resource deadlocks individually in each
	 * raid personality. (RAID5 does preallocation) We also use RR and
	 * the very same RT priority as kswapd, thus we will never get
	 * into a priority inversion deadlock.
	 *
	 * we definitely have to have equal or higher priority than
	 * bdflush, otherwise bdflush will deadlock if there are too
	 * many dirty RAID5 blocks.
	 */

	allow_signal(SIGKILL);
	while (!kthread_should_stop()) {

		/* We need to wait INTERRUPTIBLE so that
		 * we don't add to the load-average.
		 * That means we need to be sure no signals are
		 * pending
		 */
		if (signal_pending(current))
			flush_signals(current);

		wait_event_interruptible_timeout
			(thread->wqueue,
			 test_bit(THREAD_WAKEUP, &thread->flags)
			 || kthread_should_stop(),
			 thread->timeout);

		clear_bit(THREAD_WAKEUP, &thread->flags);
		if (!kthread_should_stop())
			thread->run(thread);
	}

	return 0;
}