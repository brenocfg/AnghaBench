#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int x86_vendor; int x86; int x86_model; int x86_mask; } ;
struct TYPE_8__ {int /*<<< orphan*/  evntsel; int /*<<< orphan*/  perfctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_ARCH_PERFMON_EVENTSEL0 ; 
 int /*<<< orphan*/  MSR_ARCH_PERFMON_PERFCTR0 ; 
 int /*<<< orphan*/  X86_FEATURE_ARCH_PERFMON ; 
#define  X86_VENDOR_AMD 129 
#define  X86_VENDOR_INTEL 128 
 TYPE_6__ boot_cpu_data ; 
 int /*<<< orphan*/  cpu_has (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ intel_arch_wd_ops ; 
 TYPE_1__ k7_wd_ops ; 
 TYPE_1__ p4_wd_ops ; 
 TYPE_1__ p6_wd_ops ; 
 TYPE_1__* wd_ops ; 

__attribute__((used)) static void probe_nmi_watchdog(void)
{
	switch (boot_cpu_data.x86_vendor) {
	case X86_VENDOR_AMD:
		if (boot_cpu_data.x86 == 6 ||
		    (boot_cpu_data.x86 >= 0xf && boot_cpu_data.x86 <= 0x15))
			wd_ops = &k7_wd_ops;
		return;
	case X86_VENDOR_INTEL:
		/* Work around where perfctr1 doesn't have a working enable
		 * bit as described in the following errata:
		 * AE49 Core Duo and Intel Core Solo 65 nm
		 * AN49 Intel Pentium Dual-Core
		 * AF49 Dual-Core Intel Xeon Processor LV
		 */
		if ((boot_cpu_data.x86 == 6 && boot_cpu_data.x86_model == 14) ||
		    ((boot_cpu_data.x86 == 6 && boot_cpu_data.x86_model == 15 &&
		     boot_cpu_data.x86_mask == 4))) {
			intel_arch_wd_ops.perfctr = MSR_ARCH_PERFMON_PERFCTR0;
			intel_arch_wd_ops.evntsel = MSR_ARCH_PERFMON_EVENTSEL0;
		}
		if (cpu_has(&boot_cpu_data, X86_FEATURE_ARCH_PERFMON)) {
			wd_ops = &intel_arch_wd_ops;
			break;
		}
		switch (boot_cpu_data.x86) {
		case 6:
			if (boot_cpu_data.x86_model > 13)
				return;

			wd_ops = &p6_wd_ops;
			break;
		case 15:
			wd_ops = &p4_wd_ops;
			break;
		default:
			return;
		}
		break;
	}
}