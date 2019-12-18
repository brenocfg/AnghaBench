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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  kpc_config_t ;

/* Variables and functions */
 int EPERM ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 int KPC_CLASS_RAWPMU_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ kpc_get_config_count (int) ; 
 int /*<<< orphan*/  kpc_get_configurable_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kpc_get_configurable_pmc_mask (int) ; 
 int /*<<< orphan*/  kpc_get_fixed_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpc_get_rawpmu_config (int /*<<< orphan*/ *) ; 
 scalar_t__ kpc_multiple_clients () ; 

int
kpc_get_config(uint32_t classes, kpc_config_t *current_config)
{
	uint32_t count = 0;

	assert(current_config);

	if (classes & KPC_CLASS_FIXED_MASK) {
		kpc_get_fixed_config(&current_config[count]);
		count += kpc_get_config_count(KPC_CLASS_FIXED_MASK);
	}

	if (classes & KPC_CLASS_CONFIGURABLE_MASK) {
		uint64_t pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_CONFIGURABLE_MASK);
		kpc_get_configurable_config(&current_config[count], pmc_mask);
		count += kpc_get_config_count(KPC_CLASS_CONFIGURABLE_MASK);
	}

	if (classes & KPC_CLASS_POWER_MASK) {
		uint64_t pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_POWER_MASK);
		kpc_get_configurable_config(&current_config[count], pmc_mask);
		count += kpc_get_config_count(KPC_CLASS_POWER_MASK);
	}

	if (classes & KPC_CLASS_RAWPMU_MASK)
	{
		// Client shouldn't ask for config words that aren't available.
		// Most likely, they'd misinterpret the returned buffer if we
		// allowed this.
		if( kpc_multiple_clients() )
		{
			return EPERM;
		}
		kpc_get_rawpmu_config(&current_config[count]);
		count += kpc_get_config_count(KPC_CLASS_RAWPMU_MASK);
	}

	return 0;
}