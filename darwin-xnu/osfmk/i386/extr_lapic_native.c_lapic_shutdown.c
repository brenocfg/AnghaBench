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

/* Variables and functions */
 scalar_t__ FALSE ; 
 int LAPIC_LVT_MASKED ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int LAPIC_SVR_ENABLE ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LVT_ERROR ; 
 int /*<<< orphan*/  LVT_LINT0 ; 
 int /*<<< orphan*/  LVT_PERFCNT ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 int /*<<< orphan*/  MSR_IA32_APIC_BASE ; 
 int MSR_IA32_APIC_BASE_ENABLE ; 
 int /*<<< orphan*/  SVR ; 
 int /*<<< orphan*/  cpuid_set_info () ; 
 scalar_t__ get_cpu_number () ; 
 scalar_t__ lapic_os_enabled ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

void
lapic_shutdown(void)
{
	uint32_t lo;
	uint32_t hi;
	uint32_t value;

	/* Shutdown if local APIC was enabled by OS */
	if (lapic_os_enabled == FALSE)
		return;

	mp_disable_preemption();

	/* ExtINT: masked */
	if (get_cpu_number() == master_cpu) {
		value = LAPIC_READ(LVT_LINT0);
		value |= LAPIC_LVT_MASKED;
		LAPIC_WRITE(LVT_LINT0, value);
	}

	/* Error: masked */
	LAPIC_WRITE(LVT_ERROR, LAPIC_READ(LVT_ERROR) | LAPIC_LVT_MASKED);

	/* Timer: masked */
	LAPIC_WRITE(LVT_TIMER, LAPIC_READ(LVT_TIMER) | LAPIC_LVT_MASKED);

	/* Perfmon: masked */
	LAPIC_WRITE(LVT_PERFCNT, LAPIC_READ(LVT_PERFCNT) | LAPIC_LVT_MASKED);

	/* APIC software disabled */
	LAPIC_WRITE(SVR, LAPIC_READ(SVR) & ~LAPIC_SVR_ENABLE);

	/* Bypass the APIC completely and update cpu features */
	rdmsr(MSR_IA32_APIC_BASE, lo, hi);
	lo &= ~MSR_IA32_APIC_BASE_ENABLE;
	wrmsr(MSR_IA32_APIC_BASE, lo, hi);
	cpuid_set_info();

	mp_enable_preemption();
}