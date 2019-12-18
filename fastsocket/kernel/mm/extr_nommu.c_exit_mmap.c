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
struct vm_area_struct {struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; scalar_t__ total_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_vma (struct mm_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  delete_vma_from_mm (struct vm_area_struct*) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  kleave (char*) ; 

void exit_mmap(struct mm_struct *mm)
{
	struct vm_area_struct *vma;

	if (!mm)
		return;

	kenter("");

	mm->total_vm = 0;

	while ((vma = mm->mmap)) {
		mm->mmap = vma->vm_next;
		delete_vma_from_mm(vma);
		delete_vma(mm, vma);
	}

	kleave("");
}