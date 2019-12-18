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
struct TYPE_7__ {int /*<<< orphan*/  apic_attention; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_5__ {scalar_t__ msr_val; } ;
struct TYPE_6__ {TYPE_1__ pv_eoi; } ;
struct TYPE_8__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_APIC_PV_EOI_PENDING ; 
 int /*<<< orphan*/  KVM_PV_EOI_DISABLED ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apic_debug (char*,unsigned long long) ; 
 scalar_t__ pv_eoi_put_user (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_4__* vcpi ; 

__attribute__((used)) static void pv_eoi_clr_pending(struct kvm_vcpu *vcpu)
{
	if (pv_eoi_put_user(vcpu, KVM_PV_EOI_DISABLED) < 0) {
		apic_debug("Can't clear EOI MSR value: 0x%llx\n",
			   (unsigned long long)vcpi->arch.pv_eoi.msr_val);
		return;
	}
	__clear_bit(KVM_APIC_PV_EOI_PENDING, &vcpu->arch.apic_attention);
}