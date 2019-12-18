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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_MC0_STATUS ; 
 int /*<<< orphan*/  MSR_IA32_MCG_STATUS ; 
 int /*<<< orphan*/  MSR_IA32_MCx_STATUS (int) ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 int /*<<< orphan*/  erratum_383_found ; 
 int /*<<< orphan*/  lower_32_bits (unsigned long long) ; 
 unsigned long long native_read_msr_safe (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  native_write_msr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (unsigned long long) ; 

__attribute__((used)) static bool is_erratum_383(void)
{
	int err, i;
	u64 value;

	if (!erratum_383_found)
		return false;

	value = native_read_msr_safe(MSR_IA32_MC0_STATUS, &err);
	if (err)
		return false;

	/* Bit 62 may or may not be set for this mce */
	value &= ~(1ULL << 62);

	if (value != 0xb600000000010015)
		return false;

	/* Clear MCi_STATUS registers */
	for (i = 0; i < 6; ++i)
		native_write_msr_safe(MSR_IA32_MCx_STATUS(i), 0, 0);

	value = native_read_msr_safe(MSR_IA32_MCG_STATUS, &err);
	if (!err) {
		u32 low, high;

		value &= ~(1ULL << 2);
		low    = lower_32_bits(value);
		high   = upper_32_bits(value);

		native_write_msr_safe(MSR_IA32_MCG_STATUS, low, high);
	}

	/* Flush tlb to evict multi-match entries */
	__flush_tlb_all();

	return true;
}