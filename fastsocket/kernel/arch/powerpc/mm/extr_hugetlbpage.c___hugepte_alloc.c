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
struct mm_struct {int /*<<< orphan*/  page_table_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_4__ {unsigned long pd; } ;
typedef  TYPE_1__ hugepd_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 unsigned long HUGEPD_OK ; 
 size_t HUGE_PGTABLE_INDEX (unsigned int) ; 
 int __GFP_REPEAT ; 
 int /*<<< orphan*/  hugepd_none (TYPE_1__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pgtable_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __hugepte_alloc(struct mm_struct *mm, hugepd_t *hpdp,
			   unsigned long address, unsigned int psize)
{
	pte_t *new = kmem_cache_zalloc(pgtable_cache[HUGE_PGTABLE_INDEX(psize)],
				      GFP_KERNEL|__GFP_REPEAT);

	if (! new)
		return -ENOMEM;

	spin_lock(&mm->page_table_lock);
	if (!hugepd_none(*hpdp))
		kmem_cache_free(pgtable_cache[HUGE_PGTABLE_INDEX(psize)], new);
	else
		hpdp->pd = (unsigned long)new | HUGEPD_OK;
	spin_unlock(&mm->page_table_lock);
	return 0;
}