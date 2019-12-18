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
struct vm_area_struct {unsigned long vm_start; int /*<<< orphan*/ * vm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  gru_vm_ops ; 

struct vm_area_struct *gru_find_vma(unsigned long vaddr)
{
	struct vm_area_struct *vma;

	vma = find_vma(current->mm, vaddr);
	if (vma && vma->vm_start <= vaddr && vma->vm_ops == &gru_vm_ops)
		return vma;
	return NULL;
}