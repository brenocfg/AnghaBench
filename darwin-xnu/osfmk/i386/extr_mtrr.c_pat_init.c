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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_CONTROL_PAT ; 
 int CPUID_FEATURE_PAT ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSR_IA32_CR_PAT ; 
 int cpuid_features () ; 
 int /*<<< orphan*/  get_cpu_number () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_update_action (int /*<<< orphan*/ ) ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 

void
pat_init(void)
{
	boolean_t	istate;
	uint64_t	pat;

	if (!(cpuid_features() & CPUID_FEATURE_PAT))
		return;

	istate = ml_set_interrupts_enabled(FALSE);

	pat = rdmsr64(MSR_IA32_CR_PAT);
	DBG("CPU%d PAT: was 0x%016llx\n", get_cpu_number(), pat);

	/* Change PA6 attribute field to WC if required */
	if ((pat & ~(0x0FULL << 48)) != (0x01ULL << 48)) {
		mtrr_update_action(CACHE_CONTROL_PAT);
	}
	ml_set_interrupts_enabled(istate);
}