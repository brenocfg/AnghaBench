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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int EFAULT ; 
 struct vm_area_struct* ERR_PTR (int) ; 
 unsigned long MPOL_MF_DISCONTIG_OK ; 
 unsigned long MPOL_MF_MOVE ; 
 unsigned long MPOL_MF_MOVE_ALL ; 
 unsigned long MPOL_MF_STRICT ; 
 int check_pgd_range (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/  const*,unsigned long,void*) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 
 scalar_t__ vma_migratable (struct vm_area_struct*) ; 

__attribute__((used)) static struct vm_area_struct *
check_range(struct mm_struct *mm, unsigned long start, unsigned long end,
		const nodemask_t *nodes, unsigned long flags, void *private)
{
	int err;
	struct vm_area_struct *first, *vma, *prev;


	first = find_vma(mm, start);
	if (!first)
		return ERR_PTR(-EFAULT);
	prev = NULL;
	for (vma = first; vma && vma->vm_start < end; vma = vma->vm_next) {
		if (!(flags & MPOL_MF_DISCONTIG_OK)) {
			if (!vma->vm_next && vma->vm_end < end)
				return ERR_PTR(-EFAULT);
			if (prev && prev->vm_end < vma->vm_start)
				return ERR_PTR(-EFAULT);
		}
		if (!is_vm_hugetlb_page(vma) &&
		    ((flags & MPOL_MF_STRICT) ||
		     ((flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) &&
				vma_migratable(vma)))) {
			unsigned long endvma = vma->vm_end;

			if (endvma > end)
				endvma = end;
			if (vma->vm_start > start)
				start = vma->vm_start;
			err = check_pgd_range(vma, start, endvma, nodes,
						flags, private);
			if (err) {
				first = ERR_PTR(err);
				break;
			}
		}
		prev = vma;
	}
	return first;
}