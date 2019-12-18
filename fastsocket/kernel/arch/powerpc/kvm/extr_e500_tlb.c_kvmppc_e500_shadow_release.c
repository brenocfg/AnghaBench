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
struct page {int dummy; } ;
struct kvmppc_vcpu_e500 {struct page*** shadow_pages; struct tlbe** shadow_tlb; } ;

/* Variables and functions */
 scalar_t__ get_tlb_v (struct tlbe*) ; 
 int /*<<< orphan*/  kvm_release_page_clean (struct page*) ; 
 int /*<<< orphan*/  kvm_release_page_dirty (struct page*) ; 
 scalar_t__ tlbe_is_writable (struct tlbe*) ; 

__attribute__((used)) static void kvmppc_e500_shadow_release(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int esel)
{
	struct tlbe *stlbe = &vcpu_e500->shadow_tlb[tlbsel][esel];
	struct page *page = vcpu_e500->shadow_pages[tlbsel][esel];

	if (page) {
		vcpu_e500->shadow_pages[tlbsel][esel] = NULL;

		if (get_tlb_v(stlbe)) {
			if (tlbe_is_writable(stlbe))
				kvm_release_page_dirty(page);
			else
				kvm_release_page_clean(page);
		}
	}
}