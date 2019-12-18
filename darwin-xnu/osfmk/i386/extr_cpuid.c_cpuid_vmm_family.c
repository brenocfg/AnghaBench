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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpuid_vmm_family; } ;

/* Variables and functions */
 TYPE_1__* cpuid_vmm_info () ; 

uint32_t
cpuid_vmm_family(void)
{
	return cpuid_vmm_info()->cpuid_vmm_family;
}