#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned int vm_flags; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct vm_area_struct* vm_next; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned int def_flags; struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 unsigned int VM_LOCKED ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  mlock_fixup (struct vm_area_struct*,struct vm_area_struct**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int do_mlockall(int flags)
{
	struct vm_area_struct * vma, * prev = NULL;
	unsigned int def_flags = 0;

	if (flags & MCL_FUTURE)
		def_flags = VM_LOCKED;
	current->mm->def_flags = def_flags;
	if (flags == MCL_FUTURE)
		goto out;

	for (vma = current->mm->mmap; vma ; vma = prev->vm_next) {
		unsigned int newflags;

		newflags = vma->vm_flags | VM_LOCKED;
		if (!(flags & MCL_CURRENT))
			newflags &= ~VM_LOCKED;

		/* Ignore errors */
		mlock_fixup(vma, &prev, vma->vm_start, vma->vm_end, newflags);
	}
out:
	return 0;
}