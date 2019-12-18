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
struct kvm_vcpu {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 struct kvm_vcpu* kvmppc_core_vcpu_create (struct kvm*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_create_vcpu_debugfs (struct kvm_vcpu*,unsigned int) ; 

struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm, unsigned int id)
{
	struct kvm_vcpu *vcpu;
	vcpu = kvmppc_core_vcpu_create(kvm, id);
	kvmppc_create_vcpu_debugfs(vcpu, id);
	return vcpu;
}