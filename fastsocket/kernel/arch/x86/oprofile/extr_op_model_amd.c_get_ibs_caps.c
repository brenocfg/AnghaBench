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
typedef  int u32 ;

/* Variables and functions */
 int IBS_CAPS_AVAIL ; 
 int IBS_CAPS_DEFAULT ; 
 unsigned int IBS_CPUID_FEATURES ; 
 int /*<<< orphan*/  X86_FEATURE_IBS ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 void* cpuid_eax (unsigned int) ; 

__attribute__((used)) static u32 get_ibs_caps(void)
{
	u32 ibs_caps;
	unsigned int max_level;

	if (!boot_cpu_has(X86_FEATURE_IBS))
		return 0;

	/* check IBS cpuid feature flags */
	max_level = cpuid_eax(0x80000000);
	if (max_level < IBS_CPUID_FEATURES)
		return IBS_CAPS_DEFAULT;

	ibs_caps = cpuid_eax(IBS_CPUID_FEATURES);
	if (!(ibs_caps & IBS_CAPS_AVAIL))
		/* cpuid flags not valid */
		return IBS_CAPS_DEFAULT;

	return ibs_caps;
}