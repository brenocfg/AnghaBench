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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long uint32_t ;

/* Variables and functions */
 unsigned long long CONFIGURABLE_RELOAD (unsigned long long) ; 
 unsigned long long CONFIGURABLE_SHADOW (unsigned long long) ; 
 unsigned long long KPC_ARM64_COUNTER_MASK ; 
 unsigned long long KPC_ARM64_COUNTER_OVF_MASK ; 
 int /*<<< orphan*/  assert (unsigned long long*) ; 
 unsigned long long kpc_configurable_count () ; 
 int kpc_configurable_max () ; 
 unsigned long long kpc_fixed_count () ; 
 unsigned long long read_counter (unsigned long long) ; 

int
kpc_get_configurable_counters(uint64_t *counterv, uint64_t pmc_mask)
{
	uint32_t cfg_count = kpc_configurable_count(), offset = kpc_fixed_count();
	uint64_t ctr = 0ULL;

	assert(counterv);

	for (uint32_t i = 0; i < cfg_count; ++i) {
		if (((1ULL << i) & pmc_mask) == 0)
			continue;
		ctr = read_counter(i + offset);

		if (ctr & KPC_ARM64_COUNTER_OVF_MASK) {
			ctr = CONFIGURABLE_SHADOW(i) +
				(kpc_configurable_max() - CONFIGURABLE_RELOAD(i) + 1 /* Wrap */) +
				(ctr & KPC_ARM64_COUNTER_MASK);
		} else {
			ctr = CONFIGURABLE_SHADOW(i) +
				(ctr - CONFIGURABLE_RELOAD(i));
		}

		*counterv++ = ctr;
	}

	return 0;
}