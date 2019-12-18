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
struct TYPE_6__ {scalar_t__ pending; } ;
struct TYPE_5__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; int /*<<< orphan*/  nr; scalar_t__ pending; } ;
struct TYPE_7__ {int nmi_injected; int nmi_pending; TYPE_2__ interrupt; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_irq ) (struct kvm_vcpu*) ;scalar_t__ (* interrupt_allowed ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* set_nmi ) (struct kvm_vcpu*) ;scalar_t__ (* nmi_allowed ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* queue_exception ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_cpu_get_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_interrupt (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*) ; 
 scalar_t__ stub4 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*) ; 
 scalar_t__ stub6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_inj_exception (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inject_pending_event(struct kvm_vcpu *vcpu)
{
	/* try to reinject previous events if any */
	if (vcpu->arch.exception.pending) {
		trace_kvm_inj_exception(vcpu->arch.exception.nr,
					vcpu->arch.exception.has_error_code,
					vcpu->arch.exception.error_code);
		kvm_x86_ops->queue_exception(vcpu, vcpu->arch.exception.nr,
					  vcpu->arch.exception.has_error_code,
					  vcpu->arch.exception.error_code);
		return;
	}

	if (vcpu->arch.nmi_injected) {
		kvm_x86_ops->set_nmi(vcpu);
		return;
	}

	if (vcpu->arch.interrupt.pending) {
		kvm_x86_ops->set_irq(vcpu);
		return;
	}

	/* try to inject new event if pending */
	if (vcpu->arch.nmi_pending) {
		if (kvm_x86_ops->nmi_allowed(vcpu)) {
			vcpu->arch.nmi_pending = false;
			vcpu->arch.nmi_injected = true;
			kvm_x86_ops->set_nmi(vcpu);
		}
	} else if (kvm_cpu_has_interrupt(vcpu)) {
		if (kvm_x86_ops->interrupt_allowed(vcpu)) {
			kvm_queue_interrupt(vcpu, kvm_cpu_get_interrupt(vcpu),
					    false);
			kvm_x86_ops->set_irq(vcpu);
		}
	}
}