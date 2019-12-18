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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; int /*<<< orphan*/  vm_mm; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINISH_FLUSH ; 
 scalar_t__ Hash ; 
 int /*<<< orphan*/  _tlbia () ; 
 int /*<<< orphan*/  flush_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	struct vm_area_struct *mp;

	if (Hash == 0) {
		_tlbia();
		return;
	}

	/*
	 * It is safe to go down the mm's list of vmas when called
	 * from dup_mmap, holding mmap_sem.  It would also be safe from
	 * unmap_region or exit_mmap, but not from vmtruncate on SMP -
	 * but it seems dup_mmap is the only SMP case which gets here.
	 */
	for (mp = mm->mmap; mp != NULL; mp = mp->vm_next)
		flush_range(mp->vm_mm, mp->vm_start, mp->vm_end);
	FINISH_FLUSH;
}