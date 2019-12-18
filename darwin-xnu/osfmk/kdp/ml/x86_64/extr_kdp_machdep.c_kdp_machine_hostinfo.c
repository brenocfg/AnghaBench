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
struct TYPE_4__ {int cpus_mask; int cpu_type; int /*<<< orphan*/  cpu_subtype; } ;
typedef  TYPE_1__ kdp_hostinfo_t ;
struct TYPE_5__ {int max_cpus; } ;

/* Variables and functions */
 int CPU_ARCH_ABI64 ; 
 int /*<<< orphan*/ ** cpu_data_ptr ; 
 int /*<<< orphan*/  cpuid_cpusubtype () ; 
 int cpuid_cputype () ; 
 TYPE_2__ machine_info ; 

void
kdp_machine_hostinfo(
    kdp_hostinfo_t *hostinfo
)
{
    int			i;

    hostinfo->cpus_mask = 0;

    for (i = 0; i < machine_info.max_cpus; i++) {
	if (cpu_data_ptr[i] == NULL)
            continue;
	
        hostinfo->cpus_mask |= (1 << i);
    }

    hostinfo->cpu_type = cpuid_cputype() | CPU_ARCH_ABI64;
    hostinfo->cpu_subtype = cpuid_cpusubtype();
}