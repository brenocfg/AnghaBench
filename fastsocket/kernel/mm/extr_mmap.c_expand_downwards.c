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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int acct_stack_growth (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  anon_vma_prepare (struct vm_area_struct*) ; 
 int /*<<< orphan*/  khugepaged_enter_vma_merge (struct vm_area_struct*) ; 
 int /*<<< orphan*/  perf_event_mmap (struct vm_area_struct*) ; 
 int security_file_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_lock_anon_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_unlock_anon_vma (struct vm_area_struct*) ; 

__attribute__((used)) static int expand_downwards(struct vm_area_struct *vma,
				   unsigned long address)
{
	int error;

	/*
	 * We must make sure the anon_vma is allocated
	 * so that the anon_vma locking is not a noop.
	 */
	if (unlikely(anon_vma_prepare(vma)))
		return -ENOMEM;

	address &= PAGE_MASK;
	error = security_file_mmap(NULL, 0, 0, 0, address, 1);
	if (error)
		return error;

	vma_lock_anon_vma(vma);

	/*
	 * vma->vm_start/vm_end cannot change under us because the caller
	 * is required to hold the mmap_sem in read mode.  We need the
	 * anon_vma lock to serialize against concurrent expand_stacks.
	 */

	/* Somebody else might have raced and expanded it already */
	if (address < vma->vm_start) {
		unsigned long size, grow;

		size = vma->vm_end - address;
		grow = (vma->vm_start - address) >> PAGE_SHIFT;

		error = -ENOMEM;
		if (grow <= vma->vm_pgoff) {
			error = acct_stack_growth(vma, size, grow);
			if (!error) {
				vma->vm_start = address;
				vma->vm_pgoff -= grow;
				perf_event_mmap(vma);
			}
		}
	}
	vma_unlock_anon_vma(vma);
	khugepaged_enter_vma_merge(vma);
	return error;
}