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
struct kvmppc_vcpu_e500 {int* guest_tlb_size; struct tlbe** guest_tlb; } ;
typedef  scalar_t__ gva_t ;

/* Variables and functions */
 scalar_t__ get_tlb_eaddr (struct tlbe*) ; 
 scalar_t__ get_tlb_end (struct tlbe*) ; 
 unsigned int get_tlb_tid (struct tlbe*) ; 
 int get_tlb_ts (struct tlbe*) ; 
 int /*<<< orphan*/  get_tlb_v (struct tlbe*) ; 

__attribute__((used)) static int kvmppc_e500_tlb_index(struct kvmppc_vcpu_e500 *vcpu_e500,
		gva_t eaddr, int tlbsel, unsigned int pid, int as)
{
	int i;

	/* XXX Replace loop with fancy data structures. */
	for (i = 0; i < vcpu_e500->guest_tlb_size[tlbsel]; i++) {
		struct tlbe *tlbe = &vcpu_e500->guest_tlb[tlbsel][i];
		unsigned int tid;

		if (eaddr < get_tlb_eaddr(tlbe))
			continue;

		if (eaddr > get_tlb_end(tlbe))
			continue;

		tid = get_tlb_tid(tlbe);
		if (tid && (tid != pid))
			continue;

		if (!get_tlb_v(tlbe))
			continue;

		if (get_tlb_ts(tlbe) != as && as != -1)
			continue;

		return i;
	}

	return -1;
}