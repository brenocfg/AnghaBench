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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; } ;
struct mm_struct {unsigned long shlib_base; unsigned long brk; unsigned long (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;int /*<<< orphan*/  start_brk; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 int PAGE_ALIGN (unsigned long) ; 
 unsigned long TASK_SIZE ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 unsigned long max (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long randomize_range (int,int,unsigned long) ; 
 scalar_t__ should_randomize () ; 
 unsigned long stub1 (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

unsigned long
arch_get_unmapped_exec_area(struct file *filp, unsigned long addr0,
		unsigned long len0, unsigned long pgoff, unsigned long flags)
{
	unsigned long addr = addr0, len = len0;
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	unsigned long tmp;

	if (len > TASK_SIZE)
		return -ENOMEM;

	if (flags & MAP_FIXED)
		return addr;

	if (!addr)
		addr = !should_randomize() ? mm->shlib_base :
			randomize_range(mm->shlib_base, 0x01000000, len);

	if (addr) {
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		if (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vma->vm_start))
			return addr;
	}

	addr = mm->shlib_base;
	for (vma = find_vma(mm, addr); ; vma = vma->vm_next) {
		/* At this point:  (!vma || addr < vma->vm_end). */
		if (TASK_SIZE - len < addr)
			return -ENOMEM;

		if (!vma || addr + len <= vma->vm_start) {
			/*
			 * Must not let a PROT_EXEC mapping get into the
			 * brk area:
			 */
			if (addr + len > mm->brk)
				goto failed;

			/*
			 * Up until the brk area we randomize addresses
			 * as much as possible:
			 */
			if (addr >= 0x01000000 && should_randomize()) {
				tmp = randomize_range(0x01000000,
					PAGE_ALIGN(max(mm->start_brk,
					(unsigned long)0x08000000)), len);
				vma = find_vma(mm, tmp);
				if (TASK_SIZE - len >= tmp &&
				    (!vma || tmp + len <= vma->vm_start))
					return tmp;
			}
			/*
			 * Ok, randomization didnt work out - return
			 * the result of the linear search:
			 */
			return addr;
		}
		addr = vma->vm_end;
	}

failed:
	return current->mm->get_unmapped_area(filp, addr0, len0, pgoff, flags);
}