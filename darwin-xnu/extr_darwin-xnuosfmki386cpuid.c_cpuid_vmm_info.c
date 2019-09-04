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
typedef  int /*<<< orphan*/  i386_vmm_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cpuid_vmm_info ; 
 int /*<<< orphan*/ * _cpuid_vmm_infop ; 
 int /*<<< orphan*/  cpuid_init_vmm_info (int /*<<< orphan*/ *) ; 

i386_vmm_info_t *
cpuid_vmm_info(void)
{
	if (_cpuid_vmm_infop == NULL) {
		cpuid_init_vmm_info(&_cpuid_vmm_info);
		_cpuid_vmm_infop = &_cpuid_vmm_info;
	}
	return _cpuid_vmm_infop;
}