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
struct tlbe {scalar_t__ mas1; } ;
struct kvmppc_vcpu_e500 {struct tlbe** guest_tlb; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_tlb_eaddr (struct tlbe*) ; 
 int /*<<< orphan*/  get_tlb_end (struct tlbe*) ; 
 int /*<<< orphan*/  get_tlb_iprot (struct tlbe*) ; 
 int /*<<< orphan*/  get_tlb_tid (struct tlbe*) ; 
 int /*<<< orphan*/  kvmppc_e500_stlbe_invalidate (struct kvmppc_vcpu_e500*,int,int) ; 
 int /*<<< orphan*/  kvmppc_e500_tlb1_invalidate (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_e500_gtlbe_invalidate(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int esel)
{
	struct tlbe *gtlbe = &vcpu_e500->guest_tlb[tlbsel][esel];

	if (unlikely(get_tlb_iprot(gtlbe)))
		return -1;

	if (tlbsel == 1) {
		kvmppc_e500_tlb1_invalidate(vcpu_e500, get_tlb_eaddr(gtlbe),
				get_tlb_end(gtlbe),
				get_tlb_tid(gtlbe));
	} else {
		kvmppc_e500_stlbe_invalidate(vcpu_e500, tlbsel, esel);
	}

	gtlbe->mas1 = 0;

	return 0;
}