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
struct clock_sync_data {int in_sync; int /*<<< orphan*/  fixup_cc; int /*<<< orphan*/  cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  __udelay (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  disable_sync_clock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_sync_clock () ; 
 int /*<<< orphan*/  fixup_clock_comparator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_sync_cpu(struct clock_sync_data *sync)
{
	atomic_dec(&sync->cpus);
	enable_sync_clock();
	/*
	 * This looks like a busy wait loop but it isn't. etr_sync_cpus
	 * is called on all other cpus while the TOD clocks is stopped.
	 * __udelay will stop the cpu on an enabled wait psw until the
	 * TOD is running again.
	 */
	while (sync->in_sync == 0) {
		__udelay(1);
		/*
		 * A different cpu changes *in_sync. Therefore use
		 * barrier() to force memory access.
		 */
		barrier();
	}
	if (sync->in_sync != 1)
		/* Didn't work. Clear per-cpu in sync bit again. */
		disable_sync_clock(NULL);
	/*
	 * This round of TOD syncing is done. Set the clock comparator
	 * to the next tick and let the processor continue.
	 */
	fixup_clock_comparator(sync->fixup_cc);
}