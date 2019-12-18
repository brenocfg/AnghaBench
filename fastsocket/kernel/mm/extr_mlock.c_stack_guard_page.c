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
struct vm_area_struct {int vm_flags; unsigned long vm_start; int /*<<< orphan*/  vm_prev; } ;

/* Variables and functions */
 int VM_GROWSDOWN ; 
 int /*<<< orphan*/  vma_stack_continue (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline int stack_guard_page(struct vm_area_struct *vma, unsigned long addr)
{
	return (vma->vm_flags & VM_GROWSDOWN) &&
		(vma->vm_start == addr) &&
		!vma_stack_continue(vma->vm_prev, addr);
}