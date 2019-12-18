#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union ia64_ipi_d {int /*<<< orphan*/  vector; int /*<<< orphan*/  dm; } ;
union ia64_ipi_a {int /*<<< orphan*/  eid; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  mp_state; int /*<<< orphan*/  launched; } ;
struct kvm_vcpu {int /*<<< orphan*/  wq; TYPE_5__ arch; TYPE_6__* kvm; } ;
struct kvm_run {int dummy; } ;
struct kvm_pt_regs {int /*<<< orphan*/  r1; int /*<<< orphan*/  cr_iip; } ;
struct TYPE_7__ {union ia64_ipi_d data; union ia64_ipi_a addr; } ;
struct TYPE_8__ {TYPE_1__ ipi_data; } ;
struct exit_ctl_data {TYPE_2__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  boot_gp; int /*<<< orphan*/  boot_ip; } ;
struct TYPE_10__ {TYPE_3__ rdv_sal_data; } ;
struct TYPE_12__ {TYPE_4__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MP_STATE_RUNNABLE ; 
 int handle_vm_error (struct kvm_vcpu*,struct kvm_run*) ; 
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 struct kvm_vcpu* lid_to_vcpu (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_deliver_ipi (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_pt_regs* vcpu_regs (struct kvm_vcpu*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_ipi(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	struct exit_ctl_data *p = kvm_get_exit_data(vcpu);
	struct kvm_vcpu *target_vcpu;
	struct kvm_pt_regs *regs;
	union ia64_ipi_a addr = p->u.ipi_data.addr;
	union ia64_ipi_d data = p->u.ipi_data.data;

	target_vcpu = lid_to_vcpu(vcpu->kvm, addr.id, addr.eid);
	if (!target_vcpu)
		return handle_vm_error(vcpu, kvm_run);

	if (!target_vcpu->arch.launched) {
		regs = vcpu_regs(target_vcpu);

		regs->cr_iip = vcpu->kvm->arch.rdv_sal_data.boot_ip;
		regs->r1 = vcpu->kvm->arch.rdv_sal_data.boot_gp;

		target_vcpu->arch.mp_state = KVM_MP_STATE_RUNNABLE;
		if (waitqueue_active(&target_vcpu->wq))
			wake_up_interruptible(&target_vcpu->wq);
	} else {
		vcpu_deliver_ipi(target_vcpu, data.dm, data.vector);
		if (target_vcpu != vcpu)
			kvm_vcpu_kick(target_vcpu);
	}

	return 1;
}