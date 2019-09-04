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

/* Variables and functions */
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 scalar_t__ kpc_fixed_count () ; 
 int /*<<< orphan*/  kpc_get_configurable_pmc_mask (int) ; 
 int kpc_popcount (int /*<<< orphan*/ ) ; 

uint32_t
kpc_get_counter_count(uint32_t classes)
{
	uint32_t count = 0;

	if (classes & KPC_CLASS_FIXED_MASK)
		count += kpc_fixed_count();

	if (classes & (KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_POWER_MASK)) {
		uint64_t pmc_msk = kpc_get_configurable_pmc_mask(classes);
		uint32_t pmc_cnt = kpc_popcount(pmc_msk);
		count += pmc_cnt;
	}

	return count;
}