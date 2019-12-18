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
struct TYPE_9__ {int sipi_vector; } ;
struct TYPE_10__ {TYPE_3__ arch; } ;
struct vcpu_svm {TYPE_6__* vmcb; TYPE_4__ vcpu; } ;
struct TYPE_11__ {int /*<<< orphan*/  regs_dirty; int /*<<< orphan*/  regs_avail; } ;
struct kvm_vcpu {TYPE_5__ arch; } ;
struct TYPE_7__ {int base; int selector; } ;
struct TYPE_8__ {TYPE_1__ cs; } ;
struct TYPE_12__ {TYPE_2__ save; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCB_SEG ; 
 int /*<<< orphan*/  init_vmcb (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static int svm_vcpu_reset(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	init_vmcb(svm);

	if (!kvm_vcpu_is_bsp(vcpu)) {
		kvm_rip_write(vcpu, 0);
		svm->vmcb->save.cs.base = svm->vcpu.arch.sipi_vector << 12;
		svm->vmcb->save.cs.selector = svm->vcpu.arch.sipi_vector << 8;
		mark_dirty(svm->vmcb, VMCB_SEG);
	}
	vcpu->arch.regs_avail = ~0;
	vcpu->arch.regs_dirty = ~0;

	return 0;
}