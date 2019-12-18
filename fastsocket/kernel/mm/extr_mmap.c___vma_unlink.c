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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_rb; struct vm_area_struct* vm_prev; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap_cache; int /*<<< orphan*/  mm_rb; } ;

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  arch_remove_exec_range (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
__vma_unlink(struct mm_struct *mm, struct vm_area_struct *vma,
		struct vm_area_struct *prev)
{
	struct vm_area_struct *next = vma->vm_next;

	prev->vm_next = next;
	if (next)
		next->vm_prev = prev;
	rb_erase(&vma->vm_rb, &mm->mm_rb);
	if (mm->mmap_cache == vma)
		mm->mmap_cache = prev;
	if (vma->vm_flags & VM_EXEC)
		arch_remove_exec_range(mm, vma->vm_end);
}