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
struct TYPE_2__ {int /*<<< orphan*/  user_psize; int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; void* pgd; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG_LOW (char*,struct mm_struct*,void*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  MMU_PAGE_64K ; 
 scalar_t__ REGION_ID (unsigned long) ; 
 scalar_t__ USER_REGION_ID ; 
 int _PAGE_4K_PFN ; 
 int _PAGE_NO_CACHE ; 
 int __hash_page_4K (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned long,int,int,int /*<<< orphan*/ ) ; 
 int __hash_page_64K (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,unsigned long,int,int) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_linux_pte (void*,unsigned long) ; 
 int /*<<< orphan*/  get_slice_psize (struct mm_struct*,unsigned long) ; 
 unsigned long get_vsid (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  hash_failure_debug (unsigned long,unsigned long,unsigned long,unsigned long,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  subpage_protection (void*,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int user_segment_size (unsigned long) ; 

void hash_preload(struct mm_struct *mm, unsigned long ea,
		  unsigned long access, unsigned long trap)
{
	unsigned long vsid;
	void *pgdir;
	pte_t *ptep;
	unsigned long flags;
	int rc, ssize, local = 0;

	BUG_ON(REGION_ID(ea) != USER_REGION_ID);

#ifdef CONFIG_PPC_MM_SLICES
	/* We only prefault standard pages for now */
	if (unlikely(get_slice_psize(mm, ea) != mm->context.user_psize))
		return;
#endif

	DBG_LOW("hash_preload(mm=%p, mm->pgdir=%p, ea=%016lx, access=%lx,"
		" trap=%lx\n", mm, mm->pgd, ea, access, trap);

	/* Get Linux PTE if available */
	pgdir = mm->pgd;
	if (pgdir == NULL)
		return;
	ptep = find_linux_pte(pgdir, ea);
	if (!ptep)
		return;

#ifdef CONFIG_PPC_64K_PAGES
	/* If either _PAGE_4K_PFN or _PAGE_NO_CACHE is set (and we are on
	 * a 64K kernel), then we don't preload, hash_page() will take
	 * care of it once we actually try to access the page.
	 * That way we don't have to duplicate all of the logic for segment
	 * page size demotion here
	 */
	if (pte_val(*ptep) & (_PAGE_4K_PFN | _PAGE_NO_CACHE))
		return;
#endif /* CONFIG_PPC_64K_PAGES */

	/* Get VSID */
	ssize = user_segment_size(ea);
	vsid = get_vsid(mm->context.id, ea, ssize);

	/* Hash doesn't like irqs */
	local_irq_save(flags);

	/* Is that local to this CPU ? */
	if (cpumask_equal(mm_cpumask(mm), cpumask_of(smp_processor_id())))
		local = 1;

	/* Hash it in */
#ifdef CONFIG_PPC_HAS_HASH_64K
	if (mm->context.user_psize == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap, local, ssize);
	else
#endif /* CONFIG_PPC_HAS_HASH_64K */
		rc = __hash_page_4K(ea, access, vsid, ptep, trap, local, ssize,
				    subpage_protection(pgdir, ea));

	/* Dump some info in case of hash insertion failure, they should
	 * never happen so it is really useful to know if/when they do
	 */
	if (rc == -1)
		hash_failure_debug(ea, access, vsid, trap, ssize,
				   mm->context.user_psize, pte_val(*ptep));

	local_irq_restore(flags);
}