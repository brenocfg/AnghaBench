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
struct TYPE_2__ {int /*<<< orphan*/  host_rr6; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_purge_vmm_mapping (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vti_set_rr6 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vcpu_post_transition(struct kvm_vcpu *vcpu)
{
	kvm_purge_vmm_mapping(vcpu);
	vti_set_rr6(vcpu->arch.host_rr6);
}