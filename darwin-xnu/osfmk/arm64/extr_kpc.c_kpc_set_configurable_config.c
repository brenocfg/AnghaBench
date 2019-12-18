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
typedef  int /*<<< orphan*/  kpc_config_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 unsigned long long kpc_configurable_count () ; 
 int /*<<< orphan*/ * kpc_controls_counter (unsigned long long) ; 
 unsigned long long kpc_fixed_count () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_counter_config (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kpc_set_configurable_config(kpc_config_t *configv, uint64_t pmc_mask)
{
	uint32_t cfg_count = kpc_configurable_count(), offset = kpc_fixed_count();
	boolean_t enabled;

	assert(configv);

	enabled = ml_set_interrupts_enabled(FALSE);

	for (uint32_t i = 0; i < cfg_count; ++i) {
		if (((1ULL << i) & pmc_mask) == 0)
			continue;
		assert(kpc_controls_counter(i + offset));

		set_counter_config(i + offset, *configv++);
	}

	ml_set_interrupts_enabled(enabled);

	return 0;
}