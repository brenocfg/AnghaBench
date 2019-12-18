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
struct vm_area_struct {unsigned long vm_end; int vm_flags; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 scalar_t__ copy_from_user (void*,void*,int) ; 
 scalar_t__ copy_to_user (void*,void*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int access_process_vm(struct task_struct *tsk, unsigned long addr, void *buf, int len, int write)
{
	struct vm_area_struct *vma;
	struct mm_struct *mm;

	if (addr + len < addr)
		return 0;

	mm = get_task_mm(tsk);
	if (!mm)
		return 0;

	down_read(&mm->mmap_sem);

	/* the access must start within one of the target process's mappings */
	vma = find_vma(mm, addr);
	if (vma) {
		/* don't overrun this mapping */
		if (addr + len >= vma->vm_end)
			len = vma->vm_end - addr;

		/* only read or write mappings where it is permitted */
		if (write && vma->vm_flags & VM_MAYWRITE)
			len -= copy_to_user((void *) addr, buf, len);
		else if (!write && vma->vm_flags & VM_MAYREAD)
			len -= copy_from_user(buf, (void *) addr, len);
		else
			len = 0;
	} else {
		len = 0;
	}

	up_read(&mm->mmap_sem);
	mmput(mm);
	return len;
}