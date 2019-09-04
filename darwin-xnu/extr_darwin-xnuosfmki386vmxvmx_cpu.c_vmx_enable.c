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
typedef  int uint64_t ;

/* Variables and functions */
 int CR4_VMXE ; 
 int MSR_IA32_FEATCTL_LOCK ; 
 int MSR_IA32_FEATCTL_VMXON ; 
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int get_cr4 () ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cr4 (int) ; 
 int /*<<< orphan*/  vmx_is_available () ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmx_enable(void)
{
	uint64_t msr_image;

	if (!vmx_is_available())
		return;

	/*
	 * We don't count on EFI initializing MSR_IA32_FEATURE_CONTROL
	 * and turning VMXON on and locking the bit, so we do that now.
	 */
	msr_image = rdmsr64(MSR_IA32_FEATURE_CONTROL);
	if (0 == ((msr_image & MSR_IA32_FEATCTL_LOCK)))
		wrmsr64(MSR_IA32_FEATURE_CONTROL,
			(msr_image |
			 MSR_IA32_FEATCTL_VMXON |
			 MSR_IA32_FEATCTL_LOCK));

	set_cr4(get_cr4() | CR4_VMXE);
}