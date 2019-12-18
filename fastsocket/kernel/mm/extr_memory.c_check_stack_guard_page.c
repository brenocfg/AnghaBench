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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; struct vm_area_struct* vm_prev; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_GROWSDOWN ; 
 int VM_GROWSUP ; 
 int /*<<< orphan*/  expand_stack (struct vm_area_struct*,scalar_t__) ; 
 int /*<<< orphan*/  expand_upwards (struct vm_area_struct*,scalar_t__) ; 

__attribute__((used)) static inline int check_stack_guard_page(struct vm_area_struct *vma, unsigned long address)
{
	address &= PAGE_MASK;
	if ((vma->vm_flags & VM_GROWSDOWN) && address == vma->vm_start) {
		struct vm_area_struct *prev = vma->vm_prev;

		/*
		 * Is there a mapping abutting this one below?
		 *
		 * That's only ok if it's the same stack mapping
		 * that has gotten split..
		 */
		if (prev && prev->vm_end == address)
			return prev->vm_flags & VM_GROWSDOWN ? 0 : -ENOMEM;

		expand_stack(vma, address - PAGE_SIZE);
	}
	if ((vma->vm_flags & VM_GROWSUP) && address + PAGE_SIZE == vma->vm_end) {
		struct vm_area_struct *next = vma->vm_next;

		/* As VM_GROWSDOWN but s/below/above/ */
		if (next && next->vm_start == address + PAGE_SIZE)
			return next->vm_flags & VM_GROWSUP ? 0 : -ENOMEM;

		expand_upwards(vma, address + PAGE_SIZE);
	}
	return 0;
}