#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_4__ {int* mth_counts; int /*<<< orphan*/  mth_gen; } ;
struct TYPE_5__ {TYPE_1__ t_monotonic; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int MAXRETRIES ; 
 int MAXSPINS ; 
 int MT_CORE_NFIXED ; 
 int atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_acquire ; 

int
mt_fixed_thread_counts(thread_t thread, uint64_t *counts_out)
{
	uint64_t start_gen, end_gen;
	uint64_t spins = 0, retries = 0;
	uint64_t counts[MT_CORE_NFIXED];

	/*
	 * Try to read a thread's counter values by ensuring its gen count is
	 * even.  If it's odd, it means that a thread is trying to update its
	 * counters.
	 *
	 * Spin until the gen count is even.
	 */
spin:
	start_gen = atomic_load_explicit(&thread->t_monotonic.mth_gen,
			memory_order_acquire);
retry:
	if (start_gen & 1) {
		spins++;
		if (spins > MAXSPINS) {
			return EBUSY;
		}
		goto spin;
	}

	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		counts[i] = thread->t_monotonic.mth_counts[i];
	}

	/*
	 * After reading the counters, check the gen count again.  If it is
	 * different from the value that we started with, the thread raced
	 * writing its counters with us reading them.  We need to redrive the
	 * entire operation.
	 *
	 * Go back to check if the value we just read was even and try to read
	 * again.
	 */
	end_gen = atomic_load_explicit(&thread->t_monotonic.mth_gen,
			memory_order_acquire);
	if (end_gen != start_gen) {
		retries++;
		if (retries > MAXRETRIES) {
			return EAGAIN;
		}
		start_gen = end_gen;
		goto retry;
	}

	/*
	 * Only after getting a consistent snapshot of the counters should we
	 * write them into the provided buffer.
	 */
	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		counts_out[i] = counts[i];
	}
	return 0;
}