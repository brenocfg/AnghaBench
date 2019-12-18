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
struct kvmppc_vcpu_e500 {int* guest_tlb_size; } ;
struct TYPE_2__ {int* gpr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int gva_t ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  get_cur_pid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_e500_gtlbe_invalidate (struct kvmppc_vcpu_e500*,int,int) ; 
 int kvmppc_e500_tlb_index (struct kvmppc_vcpu_e500*,int,int,int /*<<< orphan*/ ,int) ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

int kvmppc_e500_emul_tlbivax(struct kvm_vcpu *vcpu, int ra, int rb)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	unsigned int ia;
	int esel, tlbsel;
	gva_t ea;

	ea = ((ra) ? vcpu->arch.gpr[ra] : 0) + vcpu->arch.gpr[rb];

	ia = (ea >> 2) & 0x1;

	/* since we only have two TLBs, only lower bit is used. */
	tlbsel = (ea >> 3) & 0x1;

	if (ia) {
		/* invalidate all entries */
		for (esel = 0; esel < vcpu_e500->guest_tlb_size[tlbsel]; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
	} else {
		ea &= 0xfffff000;
		esel = kvmppc_e500_tlb_index(vcpu_e500, ea, tlbsel,
				get_cur_pid(vcpu), -1);
		if (esel >= 0)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, tlbsel, esel);
	}

	_tlbil_all();

	return EMULATE_DONE;
}