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
typedef  int uint32_t ;

/* Variables and functions */
 void* CONFIGURABLE_RELOAD (int) ; 
 scalar_t__ FIXED_RELOAD (int) ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 int /*<<< orphan*/  assert (unsigned long long*) ; 
 int /*<<< orphan*/  kpc_config_lock ; 
 int kpc_configurable_count () ; 
 void* kpc_configurable_max () ; 
 scalar_t__ kpc_fixed_max () ; 
 unsigned long long kpc_get_configurable_pmc_mask (int) ; 
 int kpc_get_counter_count (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
kpc_get_period(uint32_t classes, uint64_t *val)
{
	uint32_t count = 0 ;
	uint64_t pmc_mask = 0ULL;

	assert(val);

	lck_mtx_lock(&kpc_config_lock);

	if (classes & KPC_CLASS_FIXED_MASK) {
		/* convert reload values to periods */
		count = kpc_get_counter_count(KPC_CLASS_FIXED_MASK);
		for (uint32_t i = 0; i < count; ++i)
			*val++ = kpc_fixed_max() - FIXED_RELOAD(i);
	}

	if (classes & KPC_CLASS_CONFIGURABLE_MASK) {
		pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_CONFIGURABLE_MASK);

		/* convert reload values to periods */
		count = kpc_configurable_count();
		for (uint32_t i = 0; i < count; ++i)
			if ((1ULL << i) & pmc_mask)
				*val++ = kpc_configurable_max() - CONFIGURABLE_RELOAD(i);
	}

	if (classes & KPC_CLASS_POWER_MASK) {
		pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_POWER_MASK);

		/* convert reload values to periods */
		count = kpc_configurable_count();
		for (uint32_t i = 0; i < count; ++i)
			if ((1ULL << i) & pmc_mask)
				*val++ = kpc_configurable_max() - CONFIGURABLE_RELOAD(i);
	}

	lck_mtx_unlock(&kpc_config_lock);

	return 0;
}