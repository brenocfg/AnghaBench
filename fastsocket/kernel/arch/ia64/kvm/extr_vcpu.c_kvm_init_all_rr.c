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
struct TYPE_2__ {void* metaphysical_saved_rr0; void* metaphysical_saved_rr4; int mode_flags; void* metaphysical_rr0; void* metaphysical_rr4; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int GUEST_PHY_EMUL ; 
 int /*<<< orphan*/  VMX (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 size_t VRN0 ; 
 size_t VRN1 ; 
 size_t VRN2 ; 
 size_t VRN3 ; 
 size_t VRN4 ; 
 size_t VRN5 ; 
 size_t VRN7 ; 
 size_t VRN_SHIFT ; 
 int /*<<< orphan*/  ia64_dv_serialize_data () ; 
 int /*<<< orphan*/  ia64_set_psr (unsigned long) ; 
 int /*<<< orphan*/  ia64_set_rr (size_t,void*) ; 
 int /*<<< orphan*/  ia64_srlz_d () ; 
 scalar_t__ is_physical_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*) ; 
 int /*<<< orphan*/ * vrr ; 
 void* vrrtomrr (int /*<<< orphan*/ ) ; 

void kvm_init_all_rr(struct kvm_vcpu *vcpu)
{
	unsigned long psr;

	local_irq_save(psr);

	/* WARNING: not allow co-exist of both virtual mode and physical
	 * mode in same region
	 */

	vcpu->arch.metaphysical_saved_rr0 = vrrtomrr(VMX(vcpu, vrr[VRN0]));
	vcpu->arch.metaphysical_saved_rr4 = vrrtomrr(VMX(vcpu, vrr[VRN4]));

	if (is_physical_mode(vcpu)) {
		if (vcpu->arch.mode_flags & GUEST_PHY_EMUL)
			panic_vm(vcpu, "Machine Status conflicts!\n");

		ia64_set_rr((VRN0 << VRN_SHIFT), vcpu->arch.metaphysical_rr0);
		ia64_dv_serialize_data();
		ia64_set_rr((VRN4 << VRN_SHIFT), vcpu->arch.metaphysical_rr4);
		ia64_dv_serialize_data();
	} else {
		ia64_set_rr((VRN0 << VRN_SHIFT),
				vcpu->arch.metaphysical_saved_rr0);
		ia64_dv_serialize_data();
		ia64_set_rr((VRN4 << VRN_SHIFT),
				vcpu->arch.metaphysical_saved_rr4);
		ia64_dv_serialize_data();
	}
	ia64_set_rr((VRN1 << VRN_SHIFT),
			vrrtomrr(VMX(vcpu, vrr[VRN1])));
	ia64_dv_serialize_data();
	ia64_set_rr((VRN2 << VRN_SHIFT),
			vrrtomrr(VMX(vcpu, vrr[VRN2])));
	ia64_dv_serialize_data();
	ia64_set_rr((VRN3 << VRN_SHIFT),
			vrrtomrr(VMX(vcpu, vrr[VRN3])));
	ia64_dv_serialize_data();
	ia64_set_rr((VRN5 << VRN_SHIFT),
			vrrtomrr(VMX(vcpu, vrr[VRN5])));
	ia64_dv_serialize_data();
	ia64_set_rr((VRN7 << VRN_SHIFT),
			vrrtomrr(VMX(vcpu, vrr[VRN7])));
	ia64_dv_serialize_data();
	ia64_srlz_d();
	ia64_set_psr(psr);
}