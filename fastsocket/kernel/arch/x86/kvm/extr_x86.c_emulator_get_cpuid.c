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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_cpuid_entry2 {int /*<<< orphan*/  edx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  eax; } ;

/* Variables and functions */
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool emulator_get_cpuid(struct kvm_vcpu *vcpu,
			       u32 *eax, u32 *ebx, u32 *ecx, u32 *edx)
{
	struct kvm_cpuid_entry2 *cpuid = NULL;

	if (eax && ecx)
		cpuid = kvm_find_cpuid_entry(vcpu, *eax, *ecx);

	if (cpuid) {
		*eax = cpuid->eax;
		*ecx = cpuid->ecx;
		if (ebx)
			*ebx = cpuid->ebx;
		if (edx)
			*edx = cpuid->edx;
		return true;
	}

	return false;
}