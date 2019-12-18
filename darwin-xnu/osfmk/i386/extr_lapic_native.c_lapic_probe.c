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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int CPUID_FEATURE_APIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LAPIC_REDUCED_INTERRUPT_BASE ; 
 int LAPIC_START ; 
 int /*<<< orphan*/  MSR_IA32_APIC_BASE ; 
 int MSR_IA32_APIC_BASE_BASE ; 
 int MSR_IA32_APIC_BASE_ENABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int cpuid_family () ; 
 int cpuid_features () ; 
 int /*<<< orphan*/  cpuid_set_info () ; 
 int /*<<< orphan*/  lapic_interrupt_base ; 
 int /*<<< orphan*/  lapic_os_enabled ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

boolean_t
lapic_probe(void)
{
	uint32_t	lo;
	uint32_t	hi;

	if (cpuid_features() & CPUID_FEATURE_APIC)
		return TRUE;

	if (cpuid_family() == 6 || cpuid_family() == 15) {
		/*
		 * Mobile Pentiums:
		 * There may be a local APIC which wasn't enabled by BIOS.
		 * So we try to enable it explicitly.
		 */
		rdmsr(MSR_IA32_APIC_BASE, lo, hi);
		lo &= ~MSR_IA32_APIC_BASE_BASE;
		lo |= MSR_IA32_APIC_BASE_ENABLE | LAPIC_START;
		lo |= MSR_IA32_APIC_BASE_ENABLE;
		wrmsr(MSR_IA32_APIC_BASE, lo, hi);

		/*
		 * Re-initialize cpu features info and re-check.
		 */
		cpuid_set_info();
		/* We expect this codepath will never be traversed
		 * due to EFI enabling the APIC. Reducing the APIC
		 * interrupt base dynamically is not supported.
		 */
		if (cpuid_features() & CPUID_FEATURE_APIC) {
			printf("Local APIC discovered and enabled\n");
			lapic_os_enabled = TRUE;
			lapic_interrupt_base = LAPIC_REDUCED_INTERRUPT_BASE;
			return TRUE;
		}
	}

	return FALSE;
}