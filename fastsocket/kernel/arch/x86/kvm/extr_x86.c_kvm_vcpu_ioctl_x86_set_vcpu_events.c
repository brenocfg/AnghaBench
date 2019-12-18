#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  masked; int /*<<< orphan*/  pending; int /*<<< orphan*/  injected; } ;
struct TYPE_10__ {int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; scalar_t__ injected; } ;
struct TYPE_9__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; int /*<<< orphan*/  nr; int /*<<< orphan*/  injected; } ;
struct kvm_vcpu_events {int flags; int /*<<< orphan*/  sipi_vector; TYPE_5__ nmi; TYPE_3__ interrupt; TYPE_2__ exception; } ;
struct TYPE_11__ {scalar_t__ pending; int /*<<< orphan*/  soft; int /*<<< orphan*/  nr; } ;
struct TYPE_8__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  has_error_code; int /*<<< orphan*/  nr; int /*<<< orphan*/  pending; } ;
struct TYPE_13__ {int /*<<< orphan*/  sipi_vector; int /*<<< orphan*/  nmi_pending; int /*<<< orphan*/  nmi_injected; TYPE_4__ interrupt; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_6__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* set_nmi_mask ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_VCPUEVENT_VALID_NMI_PENDING ; 
 int KVM_VCPUEVENT_VALID_SIPI_VECTOR ; 
 scalar_t__ irqchip_in_kernel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pic_clear_isr_ack (int /*<<< orphan*/ ) ; 
 TYPE_7__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvm_vcpu_ioctl_x86_set_vcpu_events(struct kvm_vcpu *vcpu,
					      struct kvm_vcpu_events *events)
{
	if (events->flags & ~(KVM_VCPUEVENT_VALID_NMI_PENDING
			      | KVM_VCPUEVENT_VALID_SIPI_VECTOR))
		return -EINVAL;

	vcpu_load(vcpu);

	vcpu->arch.exception.pending = events->exception.injected;
	vcpu->arch.exception.nr = events->exception.nr;
	vcpu->arch.exception.has_error_code = events->exception.has_error_code;
	vcpu->arch.exception.error_code = events->exception.error_code;

	vcpu->arch.interrupt.pending = events->interrupt.injected;
	vcpu->arch.interrupt.nr = events->interrupt.nr;
	vcpu->arch.interrupt.soft = events->interrupt.soft;
	if (vcpu->arch.interrupt.pending && irqchip_in_kernel(vcpu->kvm))
		kvm_pic_clear_isr_ack(vcpu->kvm);

	vcpu->arch.nmi_injected = events->nmi.injected;
	if (events->flags & KVM_VCPUEVENT_VALID_NMI_PENDING)
		vcpu->arch.nmi_pending = events->nmi.pending;
	kvm_x86_ops->set_nmi_mask(vcpu, events->nmi.masked);

	if (events->flags & KVM_VCPUEVENT_VALID_SIPI_VECTOR)
		vcpu->arch.sipi_vector = events->sipi_vector;

	vcpu_put(vcpu);

	return 0;
}