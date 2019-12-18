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
struct kvm_vcpu {int dummy; } ;
struct kvm_cpuid_entry2 {int eax; } ;

/* Variables and functions */
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (struct kvm_vcpu*,int,int) ; 

__attribute__((used)) static struct kvm_cpuid_entry2* check_cpuid_limit(struct kvm_vcpu *vcpu,
                                                  u32 function, u32 index)
{
	struct kvm_cpuid_entry2 *maxlevel;

	maxlevel = kvm_find_cpuid_entry(vcpu, function & 0x80000000, 0);
	if (!maxlevel || maxlevel->eax >= function)
		return NULL;
	if (function & 0x80000000) {
		maxlevel = kvm_find_cpuid_entry(vcpu, 0, 0);
		if (!maxlevel)
			return NULL;
	}
	return kvm_find_cpuid_entry(vcpu, maxlevel->eax, index);
}