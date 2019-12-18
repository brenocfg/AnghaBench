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
typedef  int u32 ;
struct tlbe {int dummy; } ;
struct kvmppc_vcpu_e500 {unsigned int* guest_tlb_size; struct tlbe** shadow_tlb; } ;
typedef  scalar_t__ gva_t ;

/* Variables and functions */
 scalar_t__ get_tlb_eaddr (struct tlbe*) ; 
 scalar_t__ get_tlb_end (struct tlbe*) ; 
 unsigned int get_tlb_tid (struct tlbe*) ; 
 int /*<<< orphan*/  get_tlb_v (struct tlbe*) ; 
 int /*<<< orphan*/  kvmppc_e500_stlbe_invalidate (struct kvmppc_vcpu_e500*,int,unsigned int) ; 
 int /*<<< orphan*/  write_host_tlbe (struct kvmppc_vcpu_e500*,int,unsigned int) ; 

__attribute__((used)) static void kvmppc_e500_tlb1_invalidate(struct kvmppc_vcpu_e500 *vcpu_e500,
		gva_t eaddr, gva_t eend, u32 tid)
{
	unsigned int pid = tid & 0xff;
	unsigned int i;

	/* XXX Replace loop with fancy data structures. */
	for (i = 0; i < vcpu_e500->guest_tlb_size[1]; i++) {
		struct tlbe *stlbe = &vcpu_e500->shadow_tlb[1][i];
		unsigned int tid;

		if (!get_tlb_v(stlbe))
			continue;

		if (eend < get_tlb_eaddr(stlbe))
			continue;

		if (eaddr > get_tlb_end(stlbe))
			continue;

		tid = get_tlb_tid(stlbe);
		if (tid && (tid != pid))
			continue;

		kvmppc_e500_stlbe_invalidate(vcpu_e500, 1, i);
		write_host_tlbe(vcpu_e500, 1, i);
	}
}