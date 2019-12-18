#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i386_intr_func_t ;
struct TYPE_4__ {int version; } ;
struct TYPE_5__ {TYPE_1__ cpuid_arch_perf_leaf; } ;
typedef  TYPE_2__ i386_cpu_info_t ;

/* Variables and functions */
 TYPE_2__* cpuid_info () ; 
 int /*<<< orphan*/  lapic_set_pmi_func (int /*<<< orphan*/ ) ; 
 int mt_core_supported ; 
 scalar_t__ mt_pmi_x86_64 ; 

void
mt_early_init(void)
{
	i386_cpu_info_t *info = cpuid_info();
	if (info->cpuid_arch_perf_leaf.version >= 2) {
		lapic_set_pmi_func((i386_intr_func_t)mt_pmi_x86_64);
		mt_core_supported = true;
	}
}