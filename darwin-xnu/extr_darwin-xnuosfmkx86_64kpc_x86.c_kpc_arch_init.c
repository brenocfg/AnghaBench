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
typedef  int uint8_t ;
struct TYPE_4__ {int version; } ;
struct TYPE_5__ {TYPE_1__ cpuid_arch_perf_leaf; } ;
typedef  TYPE_2__ i386_cpu_info_t ;

/* Variables and functions */
 TYPE_2__* cpuid_info () ; 
 int kpc_supported ; 

void
kpc_arch_init(void)
{
	i386_cpu_info_t *info = cpuid_info();
	uint8_t version_id = info->cpuid_arch_perf_leaf.version;
	/*
	 * kpc only supports Intel PMU versions 2 and above.
	 */
	if (version_id < 2) {
		kpc_supported = false;
	}
}