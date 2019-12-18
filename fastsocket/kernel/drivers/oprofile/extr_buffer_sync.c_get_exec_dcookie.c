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
struct vm_area_struct {int vm_flags; TYPE_1__* vm_file; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 unsigned long NO_COOKIE ; 
 int VM_EXECUTABLE ; 
 unsigned long fast_get_dcookie (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long get_exec_dcookie(struct mm_struct *mm)
{
	unsigned long cookie = NO_COOKIE;
	struct vm_area_struct *vma;

	if (!mm)
		goto out;

	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		if (!vma->vm_file)
			continue;
		if (!(vma->vm_flags & VM_EXECUTABLE))
			continue;
		cookie = fast_get_dcookie(&vma->vm_file->f_path);
		break;
	}

out:
	return cookie;
}