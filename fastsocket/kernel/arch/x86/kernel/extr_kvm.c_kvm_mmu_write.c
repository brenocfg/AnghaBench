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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  op; } ;
struct kvm_mmu_op_write_pte {unsigned long pte_phys; int /*<<< orphan*/  pte_val; TYPE_1__ header; } ;
typedef  unsigned long __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_MMU_OP_WRITE_PTE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ __pa (void*) ; 
 struct page* kmap_atomic_to_page (void*) ; 
 int /*<<< orphan*/  kvm_deferred_mmu_op (struct kvm_mmu_op_write_pte*,int) ; 
 unsigned long page_to_pfn (struct page*) ; 

__attribute__((used)) static void kvm_mmu_write(void *dest, u64 val)
{
	__u64 pte_phys;
	struct kvm_mmu_op_write_pte wpte;

#ifdef CONFIG_HIGHPTE
	struct page *page;
	unsigned long dst = (unsigned long) dest;

	page = kmap_atomic_to_page(dest);
	pte_phys = page_to_pfn(page);
	pte_phys <<= PAGE_SHIFT;
	pte_phys += (dst & ~(PAGE_MASK));
#else
	pte_phys = (unsigned long)__pa(dest);
#endif
	wpte.header.op = KVM_MMU_OP_WRITE_PTE;
	wpte.pte_val = val;
	wpte.pte_phys = pte_phys;

	kvm_deferred_mmu_op(&wpte, sizeof wpte);
}