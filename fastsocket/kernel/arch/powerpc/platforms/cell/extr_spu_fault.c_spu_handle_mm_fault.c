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
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; int /*<<< orphan*/ * pgd; } ;
struct TYPE_2__ {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 unsigned long MFC_DSISR_ACCESS_DENIED ; 
 unsigned long MFC_DSISR_ACCESS_PUT ; 
 int VM_EXEC ; 
 unsigned int VM_FAULT_ERROR ; 
 unsigned int VM_FAULT_MAJOR ; 
 unsigned int VM_FAULT_OOM ; 
 unsigned int VM_FAULT_SIGBUS ; 
 int VM_GROWSDOWN ; 
 int VM_READ ; 
 int VM_WRITE ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned int handle_mm_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int spu_handle_mm_fault(struct mm_struct *mm, unsigned long ea,
		unsigned long dsisr, unsigned *flt)
{
	struct vm_area_struct *vma;
	unsigned long is_write;
	int ret;

	if (mm == NULL)
		return -EFAULT;

	if (mm->pgd == NULL)
		return -EFAULT;

	down_read(&mm->mmap_sem);
	ret = -EFAULT;
	vma = find_vma(mm, ea);
	if (!vma)
		goto out_unlock;

	if (ea < vma->vm_start) {
		if (!(vma->vm_flags & VM_GROWSDOWN))
			goto out_unlock;
		if (expand_stack(vma, ea))
			goto out_unlock;
	}

	is_write = dsisr & MFC_DSISR_ACCESS_PUT;
	if (is_write) {
		if (!(vma->vm_flags & VM_WRITE))
			goto out_unlock;
	} else {
		if (dsisr & MFC_DSISR_ACCESS_DENIED)
			goto out_unlock;
		if (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			goto out_unlock;
	}

	ret = 0;
	*flt = handle_mm_fault(mm, vma, ea, is_write ? FAULT_FLAG_WRITE : 0);
	if (unlikely(*flt & VM_FAULT_ERROR)) {
		if (*flt & VM_FAULT_OOM) {
			ret = -ENOMEM;
			goto out_unlock;
		} else if (*flt & VM_FAULT_SIGBUS) {
			ret = -EFAULT;
			goto out_unlock;
		}
		BUG();
	}

	if (*flt & VM_FAULT_MAJOR)
		current->maj_flt++;
	else
		current->min_flt++;

out_unlock:
	up_read(&mm->mmap_sem);
	return ret;
}