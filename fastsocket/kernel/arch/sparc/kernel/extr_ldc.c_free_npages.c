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
typedef  unsigned long u64 ;
struct ldc_mtable_entry {scalar_t__ mte; scalar_t__ cookie; } ;
struct iommu_arena {unsigned long limit; int /*<<< orphan*/  map; } ;
struct ldc_iommu {struct ldc_mtable_entry* page_table; struct iommu_arena arena; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long cookie_to_index (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  sun4v_ldc_revoke (unsigned long,unsigned long,scalar_t__) ; 

__attribute__((used)) static void free_npages(unsigned long id, struct ldc_iommu *iommu,
			u64 cookie, u64 size)
{
	struct iommu_arena *arena = &iommu->arena;
	unsigned long i, shift, index, npages;
	struct ldc_mtable_entry *base;

	npages = PAGE_ALIGN(((cookie & ~PAGE_MASK) + size)) >> PAGE_SHIFT;
	index = cookie_to_index(cookie, &shift);
	base = iommu->page_table + index;

	BUG_ON(index > arena->limit ||
	       (index + npages) > arena->limit);

	for (i = 0; i < npages; i++) {
		if (base->cookie)
			sun4v_ldc_revoke(id, cookie + (i << shift),
					 base->cookie);
		base->mte = 0;
		__clear_bit(index + i, arena->map);
	}
}