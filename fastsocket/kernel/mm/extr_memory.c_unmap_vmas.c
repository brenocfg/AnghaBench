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
struct zap_details {int /*<<< orphan*/ * i_mmap_lock; } ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; struct mm_struct* vm_mm; scalar_t__ vm_file; struct vm_area_struct* vm_next; } ;
struct mmu_gather {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_SHIFT ; 
 int VM_ACCOUNT ; 
 long ZAP_BLOCK_SIZE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hstate_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  is_pfn_mapping (struct vm_area_struct*) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_end (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mmu_notifier_invalidate_range_start (struct mm_struct*,unsigned long,unsigned long) ; 
 scalar_t__ need_resched () ; 
 unsigned long pages_per_huge_page (int /*<<< orphan*/ ) ; 
 scalar_t__ spin_needbreak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlb_finish_mmu (struct mmu_gather*,unsigned long,unsigned long) ; 
 struct mmu_gather* tlb_gather_mmu (struct mm_struct*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_hugepage_range (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long unmap_page_range (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long,long*,struct zap_details*) ; 
 int /*<<< orphan*/  untrack_pfn_vma (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long unmap_vmas(struct mmu_gather **tlbp,
		struct vm_area_struct *vma, unsigned long start_addr,
		unsigned long end_addr, unsigned long *nr_accounted,
		struct zap_details *details, int fullmm)
{
	long zap_work = ZAP_BLOCK_SIZE;
	unsigned long tlb_start = 0;	/* For tlb_finish_mmu */
	int tlb_start_valid = 0;
	unsigned long start = start_addr;
	spinlock_t *i_mmap_lock = details? details->i_mmap_lock: NULL;
	struct mm_struct *mm = vma->vm_mm;

	/*
	 * mmu_notifier_invalidate_range_start can sleep. Don't initialize
	 * mmu_gather until it completes
	 */
	mmu_notifier_invalidate_range_start(mm, start_addr, end_addr);
	*tlbp = tlb_gather_mmu(mm, fullmm);
	for ( ; vma && vma->vm_start < end_addr; vma = vma->vm_next) {
		unsigned long end;

		start = max(vma->vm_start, start_addr);
		if (start >= vma->vm_end)
			continue;
		end = min(vma->vm_end, end_addr);
		if (end <= vma->vm_start)
			continue;

		if (vma->vm_flags & VM_ACCOUNT)
			*nr_accounted += (end - start) >> PAGE_SHIFT;

		if (unlikely(is_pfn_mapping(vma)))
			untrack_pfn_vma(vma, 0, 0);

		while (start != end) {
			if (!tlb_start_valid) {
				tlb_start = start;
				tlb_start_valid = 1;
			}

			if (unlikely(is_vm_hugetlb_page(vma))) {
				/*
				 * It is undesirable to test vma->vm_file as it
				 * should be non-null for valid hugetlb area.
				 * However, vm_file will be NULL in the error
				 * cleanup path of do_mmap_pgoff. When
				 * hugetlbfs ->mmap method fails,
				 * do_mmap_pgoff() nullifies vma->vm_file
				 * before calling this function to clean up.
				 * Since no pte has actually been setup, it is
				 * safe to do nothing in this case.
				 */
				if (vma->vm_file) {
					unmap_hugepage_range(vma, start, end, NULL);
					zap_work -= (end - start) /
					pages_per_huge_page(hstate_vma(vma));
				}

				start = end;
			} else
				start = unmap_page_range(*tlbp, vma,
						start, end, &zap_work, details);

			if (zap_work > 0) {
				BUG_ON(start != end);
				break;
			}

			tlb_finish_mmu(*tlbp, tlb_start, start);

			if (need_resched() ||
				(i_mmap_lock && spin_needbreak(i_mmap_lock))) {
				if (i_mmap_lock) {
					*tlbp = NULL;
					goto out;
				}
				cond_resched();
			}

			*tlbp = tlb_gather_mmu(vma->vm_mm, fullmm);
			tlb_start_valid = 0;
			zap_work = ZAP_BLOCK_SIZE;
		}
	}
out:
	mmu_notifier_invalidate_range_end(mm, start_addr, end_addr);
	return start;	/* which is now the end (or restart) address */
}