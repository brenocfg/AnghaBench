#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  irq_window_exits; } ;
struct TYPE_8__ {TYPE_1__ stat; int /*<<< orphan*/  kvm; struct kvm_run* run; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_3__* vmcb; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; scalar_t__ request_interrupt_window; } ;
struct TYPE_6__ {int /*<<< orphan*/  int_ctl; } ;
struct TYPE_7__ {TYPE_2__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EXIT_IRQ_WINDOW_OPEN ; 
 int /*<<< orphan*/  VMCB_INTR ; 
 int /*<<< orphan*/  V_IRQ_MASK ; 
 int /*<<< orphan*/  irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_cpu_has_interrupt (TYPE_4__*) ; 
 int /*<<< orphan*/  mark_dirty (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svm_clear_vintr (struct vcpu_svm*) ; 

__attribute__((used)) static int interrupt_window_interception(struct vcpu_svm *svm)
{
	struct kvm_run *kvm_run = svm->vcpu.run;

	svm_clear_vintr(svm);
	svm->vmcb->control.int_ctl &= ~V_IRQ_MASK;
	mark_dirty(svm->vmcb, VMCB_INTR);
	/*
	 * If the user space waits to inject interrupts, exit as soon as
	 * possible
	 */
	if (!irqchip_in_kernel(svm->vcpu.kvm) &&
	    kvm_run->request_interrupt_window &&
	    !kvm_cpu_has_interrupt(&svm->vcpu)) {
		++svm->vcpu.stat.irq_window_exits;
		kvm_run->exit_reason = KVM_EXIT_IRQ_WINDOW_OPEN;
		return 0;
	}

	return 1;
}