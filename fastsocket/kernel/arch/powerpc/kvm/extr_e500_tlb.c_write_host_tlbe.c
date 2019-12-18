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
struct kvmppc_vcpu_e500 {struct tlbe** shadow_tlb; } ;

/* Variables and functions */
 unsigned int MAS0_ESEL (int /*<<< orphan*/ ) ; 
 unsigned int MAS0_TLBSEL (int) ; 
 int /*<<< orphan*/  SPRN_MAS0 ; 
 int /*<<< orphan*/  __write_host_tlbe (struct tlbe*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  to_htlb1_esel (int) ; 

__attribute__((used)) static inline void write_host_tlbe(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int esel)
{
	struct tlbe *stlbe = &vcpu_e500->shadow_tlb[tlbsel][esel];

	local_irq_disable();
	if (tlbsel == 0) {
		__write_host_tlbe(stlbe);
	} else {
		unsigned register mas0;

		mas0 = mfspr(SPRN_MAS0);

		mtspr(SPRN_MAS0, MAS0_TLBSEL(1) | MAS0_ESEL(to_htlb1_esel(esel)));
		__write_host_tlbe(stlbe);

		mtspr(SPRN_MAS0, mas0);
	}
	local_irq_enable();
}