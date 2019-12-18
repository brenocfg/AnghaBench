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
struct tlbe {int dummy; } ;
struct kvmppc_vcpu_e500 {struct tlbe** guest_tlb; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  get_tlb_eaddr (struct tlbe*) ; 
 int get_tlb_raddr (struct tlbe*) ; 
 int /*<<< orphan*/  kvmppc_e500_shadow_map (struct kvmppc_vcpu_e500*,int /*<<< orphan*/ ,int,struct tlbe*,int,int) ; 

__attribute__((used)) static int kvmppc_e500_stlbe_map(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int esel)
{
	struct tlbe *gtlbe;

	gtlbe = &vcpu_e500->guest_tlb[tlbsel][esel];

	kvmppc_e500_shadow_map(vcpu_e500, get_tlb_eaddr(gtlbe),
			get_tlb_raddr(gtlbe) >> PAGE_SHIFT,
			gtlbe, tlbsel, esel);

	return esel;
}