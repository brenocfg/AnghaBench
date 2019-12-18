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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_mm; struct vm_area_struct* vm_next; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  anon_vma; int /*<<< orphan*/  vm_flags; scalar_t__ vm_pgoff; } ;
struct mm_struct {int dummy; } ;
struct mempolicy {int dummy; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long PAGE_SHIFT ; 
 struct vm_area_struct* find_vma_prev (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 unsigned long max (unsigned long,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ mpol_equal (int /*<<< orphan*/ ,struct mempolicy*) ; 
 int policy_vma (struct vm_area_struct*,struct mempolicy*) ; 
 int split_vma (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct mempolicy*) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 

__attribute__((used)) static int mbind_range(struct mm_struct *mm, unsigned long start,
		       unsigned long end, struct mempolicy *new_pol)
{
	struct vm_area_struct *next;
	struct vm_area_struct *prev;
	struct vm_area_struct *vma;
	int err = 0;
	pgoff_t pgoff;
	unsigned long vmstart;
	unsigned long vmend;

	vma = find_vma_prev(mm, start, &prev);
	if (!vma || vma->vm_start > start)
		return -EFAULT;

	if (start > vma->vm_start)
		prev = vma;

	for (; vma && vma->vm_start < end; prev = vma, vma = next) {
		next = vma->vm_next;
		vmstart = max(start, vma->vm_start);
		vmend   = min(end, vma->vm_end);

		if (mpol_equal(vma_policy(vma), new_pol))
			continue;

		pgoff = vma->vm_pgoff +
			((vmstart - vma->vm_start) >> PAGE_SHIFT);
		prev = vma_merge(mm, prev, vmstart, vmend, vma->vm_flags,
				  vma->anon_vma, vma->vm_file, pgoff,
				  new_pol);
		if (prev) {
			vma = prev;
			next = vma->vm_next;
			continue;
		}
		if (vma->vm_start != vmstart) {
			err = split_vma(vma->vm_mm, vma, vmstart, 1);
			if (err)
				goto out;
		}
		if (vma->vm_end != vmend) {
			err = split_vma(vma->vm_mm, vma, vmend, 0);
			if (err)
				goto out;
		}
		err = policy_vma(vma, new_pol);
		if (err)
			goto out;
	}

 out:
	return err;
}