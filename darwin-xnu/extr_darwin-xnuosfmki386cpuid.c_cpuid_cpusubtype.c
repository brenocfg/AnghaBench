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
typedef  int /*<<< orphan*/  cpu_subtype_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpuid_cpu_subtype; } ;

/* Variables and functions */
 TYPE_1__* cpuid_info () ; 

cpu_subtype_t
cpuid_cpusubtype(void)
{
	return cpuid_info()->cpuid_cpu_subtype;
}