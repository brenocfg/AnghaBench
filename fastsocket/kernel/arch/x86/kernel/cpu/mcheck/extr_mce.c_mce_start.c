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
typedef  int u64 ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  SPINUNIT ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  global_nwo ; 
 int /*<<< orphan*/  mce_callin ; 
 int /*<<< orphan*/  mce_executing ; 
 scalar_t__ mce_timed_out (int*) ; 
 scalar_t__ monarch_timeout ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int mce_start(int *no_way_out)
{
	int order;
	int cpus = num_online_cpus();
	u64 timeout = (u64)monarch_timeout * NSEC_PER_USEC;

	if (!timeout)
		return -1;

	atomic_add(*no_way_out, &global_nwo);
	/*
	 * global_nwo should be updated before mce_callin
	 */
	smp_wmb();
	order = atomic_inc_return(&mce_callin);

	/*
	 * Wait for everyone.
	 */
	while (atomic_read(&mce_callin) != cpus) {
		if (mce_timed_out(&timeout)) {
			atomic_set(&global_nwo, 0);
			return -1;
		}
		ndelay(SPINUNIT);
	}

	/*
	 * mce_callin should be read before global_nwo
	 */
	smp_rmb();

	if (order == 1) {
		/*
		 * Monarch: Starts executing now, the others wait.
		 */
		atomic_set(&mce_executing, 1);
	} else {
		/*
		 * Subject: Now start the scanning loop one by one in
		 * the original callin order.
		 * This way when there are any shared banks it will be
		 * only seen by one CPU before cleared, avoiding duplicates.
		 */
		while (atomic_read(&mce_executing) < order) {
			if (mce_timed_out(&timeout)) {
				atomic_set(&global_nwo, 0);
				return -1;
			}
			ndelay(SPINUNIT);
		}
	}

	/*
	 * Cache the global no_way_out state.
	 */
	*no_way_out = atomic_read(&global_nwo);

	return order;
}