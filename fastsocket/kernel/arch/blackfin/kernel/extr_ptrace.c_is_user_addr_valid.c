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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct task_struct {TYPE_2__* mm; } ;
struct sram_list_struct {unsigned long length; scalar_t__ addr; struct sram_list_struct* next; } ;
struct TYPE_3__ {struct sram_list_struct* sram_list; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int EIO ; 
 unsigned long FIXED_CODE_END ; 
 unsigned long FIXED_CODE_START ; 
 struct vm_area_struct* find_vma (TYPE_2__*,unsigned long) ; 

__attribute__((used)) static inline int is_user_addr_valid(struct task_struct *child,
				     unsigned long start, unsigned long len)
{
	struct vm_area_struct *vma;
	struct sram_list_struct *sraml;

	/* overflow */
	if (start + len < start)
		return -EIO;

	vma = find_vma(child->mm, start);
	if (vma && start >= vma->vm_start && start + len <= vma->vm_end)
			return 0;

	for (sraml = child->mm->context.sram_list; sraml; sraml = sraml->next)
		if (start >= (unsigned long)sraml->addr
		    && start + len < (unsigned long)sraml->addr + sraml->length)
			return 0;

	if (start >= FIXED_CODE_START && start + len < FIXED_CODE_END)
		return 0;

	return -EIO;
}