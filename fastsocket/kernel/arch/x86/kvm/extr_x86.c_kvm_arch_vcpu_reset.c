#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ msr_val; } ;
struct TYPE_5__ {int nmi_pending; int nmi_injected; int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/  db; TYPE_1__ st; scalar_t__ switch_db_regs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {int (* vcpu_reset ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DR6_FIXED_1 ; 
 int /*<<< orphan*/  DR7_FIXED_1 ; 
 int /*<<< orphan*/  kvm_pmu_reset (struct kvm_vcpu*) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_reset (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_reset(struct kvm_vcpu *vcpu)
{
	vcpu->arch.nmi_pending = false;
	vcpu->arch.nmi_injected = false;

	vcpu->arch.switch_db_regs = 0;
	vcpu->arch.st.msr_val = 0;
	memset(vcpu->arch.db, 0, sizeof(vcpu->arch.db));
	vcpu->arch.dr6 = DR6_FIXED_1;
	vcpu->arch.dr7 = DR7_FIXED_1;

	kvmclock_reset(vcpu);
	kvm_pmu_reset(vcpu);

	return kvm_x86_ops->vcpu_reset(vcpu);
}