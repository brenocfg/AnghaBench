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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  mt_pmi_fn ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int MT_CORE_NFIXED ; 
 scalar_t__ MT_MIN_FIXED_PERIOD ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int mt_microstackshot_ctr ; 
 void* mt_microstackshot_ctx ; 
 int /*<<< orphan*/  mt_microstackshot_pmi_handler ; 
 int mt_microstackshot_start_arch (scalar_t__) ; 
 int mt_microstackshots ; 

int
mt_microstackshot_start(unsigned int ctr, uint64_t period, mt_pmi_fn handler,
		void *ctx)
{
	assert(ctr < MT_CORE_NFIXED);

	if (period < MT_MIN_FIXED_PERIOD) {
		return EINVAL;
	}
	if (mt_microstackshots) {
		return EBUSY;
	}

	mt_microstackshot_ctr = ctr;
	mt_microstackshot_pmi_handler = handler;
	mt_microstackshot_ctx = ctx;

	int error = mt_microstackshot_start_arch(period);
	if (error) {
		return error;
	}

	mt_microstackshots = true;

	return 0;
}