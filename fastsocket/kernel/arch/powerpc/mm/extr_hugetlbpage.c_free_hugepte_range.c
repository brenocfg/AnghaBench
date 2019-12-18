#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mmu_gather {int need_flush; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_4__ {scalar_t__ pd; } ;
typedef  TYPE_1__ hugepd_t ;

/* Variables and functions */
 scalar_t__ HUGEPTE_CACHE_NUM ; 
 int /*<<< orphan*/  PGF_CACHENUM_MASK ; 
 int /*<<< orphan*/ * hugepd_page (TYPE_1__) ; 
 int /*<<< orphan*/  pgtable_free_cache (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgtable_free_tlb (struct mmu_gather*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_hugepte_range(struct mmu_gather *tlb, hugepd_t *hpdp,
			       unsigned int psize)
{
	pte_t *hugepte = hugepd_page(*hpdp);

	hpdp->pd = 0;
	tlb->need_flush = 1;
	pgtable_free_tlb(tlb, pgtable_free_cache(hugepte,
						 HUGEPTE_CACHE_NUM+psize-1,
						 PGF_CACHENUM_MASK));
}