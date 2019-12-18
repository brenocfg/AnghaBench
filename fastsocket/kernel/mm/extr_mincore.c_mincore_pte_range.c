#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_2__ swp_entry_t ;
struct vm_area_struct {TYPE_1__* vm_file; int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_5__ {int /*<<< orphan*/ * f_mapping; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_migration_entry (TYPE_2__) ; 
 unsigned char mincore_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mincore_unmapped_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned char*) ; 
 scalar_t__ pte_file (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_pgoff (int /*<<< orphan*/ ) ; 
 TYPE_2__ pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swapper_space ; 

__attribute__((used)) static void mincore_pte_range(struct vm_area_struct *vma, pmd_t *pmd,
			unsigned long addr, unsigned long end,
			unsigned char *vec)
{
	unsigned long next;
	spinlock_t *ptl;
	pte_t *ptep;

	ptep = pte_offset_map_lock(vma->vm_mm, pmd, addr, &ptl);
	do {
		pte_t pte = *ptep;
		pgoff_t pgoff;

		next = addr + PAGE_SIZE;
		if (pte_none(pte))
			mincore_unmapped_range(vma, addr, next, vec);
		else if (pte_present(pte))
			*vec = 1;
		else if (pte_file(pte)) {
			pgoff = pte_to_pgoff(pte);
			*vec = mincore_page(vma->vm_file->f_mapping, pgoff);
		} else { /* pte is a swap entry */
			swp_entry_t entry = pte_to_swp_entry(pte);

			if (is_migration_entry(entry)) {
				/* migration entries are always uptodate */
				*vec = 1;
			} else {
#ifdef CONFIG_SWAP
				pgoff = entry.val;
				*vec = mincore_page(&swapper_space, pgoff);
#else
				WARN_ON(1);
				*vec = 1;
#endif
			}
		}
		vec++;
	} while (ptep++, addr = next, addr != end);
	pte_unmap_unlock(ptep - 1, ptl);
}