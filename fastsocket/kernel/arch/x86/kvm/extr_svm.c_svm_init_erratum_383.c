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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_AMD64_DC_CFG ; 
 TYPE_1__ boot_cpu_data ; 
 int erratum_383_found ; 
 int /*<<< orphan*/  lower_32_bits (unsigned long long) ; 
 unsigned long long native_read_msr_safe (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  native_write_msr_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (unsigned long long) ; 

__attribute__((used)) static void svm_init_erratum_383(void)
{
	u32 low, high;
	int err;
	u64 val;

	/* Only Fam10h is affected */
	if (boot_cpu_data.x86 != 0x10)
		return;

	/* Use _safe variants to not break nested virtualization */
	val = native_read_msr_safe(MSR_AMD64_DC_CFG, &err);
	if (err)
		return;

	val |= (1ULL << 47);

	low  = lower_32_bits(val);
	high = upper_32_bits(val);

	native_write_msr_safe(MSR_AMD64_DC_CFG, low, high);

	erratum_383_found = true;
}