#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int cpu_id; } ;

/* Variables and functions */
 int FALSE ; 
 int KPC_CLASS_CONFIGURABLE_MASK ; 
 int KPC_CLASS_FIXED_MASK ; 
 int KPC_CLASS_POWER_MASK ; 
 int /*<<< orphan*/  assert (unsigned long long*) ; 
 TYPE_1__* current_processor () ; 
 int /*<<< orphan*/  kpc_get_configurable_counters (unsigned long long*,unsigned long long) ; 
 unsigned long long kpc_get_configurable_pmc_mask (int) ; 
 scalar_t__ kpc_get_counter_count (int) ; 
 int /*<<< orphan*/  kpc_get_fixed_counters (unsigned long long*) ; 
 scalar_t__ kpc_popcount (unsigned long long) ; 
 int ml_set_interrupts_enabled (int) ; 

int
kpc_get_curcpu_counters(uint32_t classes, int *curcpu, uint64_t *buf)
{
	int enabled=0, offset=0;
	uint64_t pmc_mask = 0ULL;

	assert(buf);

	enabled = ml_set_interrupts_enabled(FALSE);

	/* grab counters and CPU number as close as possible */
	if (curcpu)
		*curcpu = current_processor()->cpu_id;

	if (classes & KPC_CLASS_FIXED_MASK) {
		kpc_get_fixed_counters(&buf[offset]);
		offset += kpc_get_counter_count(KPC_CLASS_FIXED_MASK);
	}

	if (classes & KPC_CLASS_CONFIGURABLE_MASK) {
		pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_CONFIGURABLE_MASK);
		kpc_get_configurable_counters(&buf[offset], pmc_mask);
		offset += kpc_popcount(pmc_mask);
	}

	if (classes & KPC_CLASS_POWER_MASK) {
		pmc_mask = kpc_get_configurable_pmc_mask(KPC_CLASS_POWER_MASK);
		kpc_get_configurable_counters(&buf[offset], pmc_mask);
		offset += kpc_popcount(pmc_mask);
	}

	ml_set_interrupts_enabled(enabled);

	return offset;
}