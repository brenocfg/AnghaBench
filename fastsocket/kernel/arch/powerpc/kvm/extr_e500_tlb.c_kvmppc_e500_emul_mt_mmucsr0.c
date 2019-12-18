#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ulong ;
struct kvmppc_vcpu_e500 {int* guest_tlb_size; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int MMUCSR0_TLB0FI ; 
 int MMUCSR0_TLB1FI ; 
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  kvmppc_e500_gtlbe_invalidate (struct kvmppc_vcpu_e500*,int,int) ; 

int kvmppc_e500_emul_mt_mmucsr0(struct kvmppc_vcpu_e500 *vcpu_e500, ulong value)
{
	int esel;

	if (value & MMUCSR0_TLB0FI)
		for (esel = 0; esel < vcpu_e500->guest_tlb_size[0]; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 0, esel);
	if (value & MMUCSR0_TLB1FI)
		for (esel = 0; esel < vcpu_e500->guest_tlb_size[1]; esel++)
			kvmppc_e500_gtlbe_invalidate(vcpu_e500, 1, esel);

	_tlbil_all();

	return EMULATE_DONE;
}