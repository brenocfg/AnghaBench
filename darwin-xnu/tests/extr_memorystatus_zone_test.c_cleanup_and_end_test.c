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
struct TYPE_2__ {int num_zones; int /*<<< orphan*/ * zone_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  T_LOG (char*,...) ; 
 int /*<<< orphan*/ * child_pids ; 
 TYPE_1__ current_test ; 
 int /*<<< orphan*/  dispatch_source_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_source_cancel_and_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ds_signal ; 
 int /*<<< orphan*/ * ds_timer ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrace_end (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  mach_zone_force_gc (int /*<<< orphan*/ ) ; 
 int num_children ; 
 int /*<<< orphan*/  print_zone_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * session ; 
 int /*<<< orphan*/  sleep (int) ; 
 int test_ending ; 
 int /*<<< orphan*/  test_ending_mtx ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  within_dispatch_signal_handler ; 
 int /*<<< orphan*/  within_dispatch_timer_handler ; 
 int /*<<< orphan*/ * zone_info_array ; 

__attribute__((used)) static void cleanup_and_end_test(void)
{
	int i;

	/*
	 * The atend handler executes on a different dispatch queue.
	 * We want to do the cleanup only once.
	 */
	pthread_mutex_lock(&test_ending_mtx);
	if (test_ending) {
		pthread_mutex_unlock(&test_ending_mtx);
		return;
	}
	test_ending = true;
	pthread_mutex_unlock(&test_ending_mtx);

	T_LOG("Number of processes spawned: %d", num_children);
	T_LOG("Cleaning up...");

	/* Disable the timer that queries and prints zone info periodically */
	if (ds_timer != NULL && !within_dispatch_timer_handler) {
		dispatch_source_cancel(ds_timer);
	}

	/* Disable signal handler that spawns child processes, only if we're not in the event handler's context */
	if (ds_signal != NULL && !within_dispatch_signal_handler) {
		dispatch_source_cancel_and_wait(ds_signal);
	}

	/* Kill all the child processes that were spawned */
	for (i = 0; i < num_children; i++) {
		kill(child_pids[i], SIGKILL);
		/*
		 * Sleep between kills to avoid hogging the VM map entries zone lock (on the task_terminate path).
		 * Without this we were seeing hw_lock_bit timeouts in BATS.
		 */
		sleep(1);
	}
	for (i = 0; i < num_children; i++) {
		int status = 0;
		if (waitpid(child_pids[i], &status, 0) < 0) {
			T_LOG("waitpid returned status %d", status);
		}
	}
	sleep(1);

	/* Force zone_gc before starting test for another zone or exiting */
	mach_zone_force_gc(mach_host_self());

	/* End ktrace session */
	if (session != NULL) {
		ktrace_end(session, 1);
	}

	for (i = 0; i < current_test.num_zones; i++) {
		print_zone_info(&(current_test.zone_names[i]), &(zone_info_array[i]));
	}
}