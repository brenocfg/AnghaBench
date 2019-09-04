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

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_counter_config (unsigned long long) ; 
 unsigned long long kpc_configurable_count () ; 
 unsigned long long kpc_fixed_count () ; 

int
kpc_get_configurable_config(kpc_config_t *configv, uint64_t pmc_mask)
{
	uint32_t cfg_count = kpc_configurable_count(), offset = kpc_fixed_count();

	assert(configv);

	for (uint32_t i = 0; i < cfg_count; ++i)
		if ((1ULL << i) & pmc_mask)
			*configv++ = get_counter_config(i + offset);
	return 0;
}