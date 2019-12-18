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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  width; } ;
struct TYPE_5__ {TYPE_1__ cpuid_arch_perf_leaf; } ;
typedef  TYPE_2__ i386_cpu_info_t ;

/* Variables and functions */
 TYPE_2__* cpuid_info () ; 

__attribute__((used)) static uint8_t
kpc_configurable_width(void)
{
	i386_cpu_info_t	*info = NULL;

	info = cpuid_info();

	return info->cpuid_arch_perf_leaf.width;
}