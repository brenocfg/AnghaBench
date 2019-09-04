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
typedef  int uint32_t ;
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;

/* Variables and functions */
 int FASTTRAP_CLEANUP_PROVIDER ; 
 int FASTTRAP_CLEANUP_TRACEPOINT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int atomic_and_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_cleanup_mtx ; 
 int /*<<< orphan*/  fasttrap_cleanup_work ; 
 int /*<<< orphan*/  fasttrap_pid_cleanup_compute_priority () ; 
 unsigned int fasttrap_pid_cleanup_providers () ; 
 int /*<<< orphan*/  fasttrap_tracepoint_cleanup () ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (void (*) (),int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct timespec*) ; 

__attribute__((used)) __attribute__((noreturn))
static void
fasttrap_pid_cleanup_cb(void)
{
	uint32_t work = 0;
	lck_mtx_lock(&fasttrap_cleanup_mtx);
	msleep(&fasttrap_pid_cleanup_cb, &fasttrap_cleanup_mtx, PRIBIO, "fasttrap_pid_cleanup_cb", NULL);
	while (1) {
		unsigned int later = 0;

		work = atomic_and_32(&fasttrap_cleanup_work, 0);
		lck_mtx_unlock(&fasttrap_cleanup_mtx);
		if (work & FASTTRAP_CLEANUP_PROVIDER) {
			later = fasttrap_pid_cleanup_providers();
		}
		if (work & FASTTRAP_CLEANUP_TRACEPOINT) {
			fasttrap_tracepoint_cleanup();
		}
		lck_mtx_lock(&fasttrap_cleanup_mtx);

		fasttrap_pid_cleanup_compute_priority();
		if (!fasttrap_cleanup_work) {
			/*
			 * If we were unable to remove a retired provider, try again after
			 * a second. This situation can occur in certain circumstances where
			 * providers cannot be unregistered even though they have no probes
			 * enabled because of an execution of dtrace -l or something similar.
			 * If the timeout has been disabled (set to 1 because we're trying
			 * to detach), we set fasttrap_cleanup_work to ensure that we'll
			 * get a chance to do that work if and when the timeout is reenabled
			 * (if detach fails).
			 */
			if (later > 0) {
				struct timespec t = {1, 0};
				msleep(&fasttrap_pid_cleanup_cb, &fasttrap_cleanup_mtx, PRIBIO, "fasttrap_pid_cleanup_cb", &t);
			}
			else
				msleep(&fasttrap_pid_cleanup_cb, &fasttrap_cleanup_mtx, PRIBIO, "fasttrap_pid_cleanup_cb", NULL);
		}
	}

}