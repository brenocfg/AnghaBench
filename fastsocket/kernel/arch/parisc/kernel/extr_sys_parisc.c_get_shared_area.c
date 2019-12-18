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
struct vm_area_struct {unsigned long vm_start; int vm_end; struct vm_area_struct* vm_next; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int DCACHE_ALIGN (int) ; 
 unsigned long ENOMEM ; 
 unsigned long TASK_SIZE ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (int /*<<< orphan*/ ,unsigned long) ; 
 int get_offset (struct address_space*) ; 

__attribute__((used)) static unsigned long get_shared_area(struct address_space *mapping,
		unsigned long addr, unsigned long len, unsigned long pgoff)
{
	struct vm_area_struct *vma;
	int offset = mapping ? get_offset(mapping) : 0;

	addr = DCACHE_ALIGN(addr - offset) + offset;

	for (vma = find_vma(current->mm, addr); ; vma = vma->vm_next) {
		/* At this point:  (!vma || addr < vma->vm_end). */
		if (TASK_SIZE - len < addr)
			return -ENOMEM;
		if (!vma || addr + len <= vma->vm_start)
			return addr;
		addr = DCACHE_ALIGN(vma->vm_end - offset) + offset;
		if (addr < vma->vm_end) /* handle wraparound */
			return -ENOMEM;
	}
}