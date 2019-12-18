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
struct vm_area_struct {struct mempolicy* vm_policy; TYPE_1__* vm_ops; } ;
struct task_struct {struct mempolicy* mempolicy; } ;
struct mempolicy {int dummy; } ;
struct TYPE_2__ {struct mempolicy* (* get_policy ) (struct vm_area_struct*,unsigned long) ;} ;

/* Variables and functions */
 struct mempolicy default_policy ; 
 struct mempolicy* stub1 (struct vm_area_struct*,unsigned long) ; 

struct mempolicy *get_vma_policy(struct task_struct *task,
		struct vm_area_struct *vma, unsigned long addr)
{
	struct mempolicy *pol = task->mempolicy;

	if (vma) {
		if (vma->vm_ops && vma->vm_ops->get_policy) {
			struct mempolicy *vpol = vma->vm_ops->get_policy(vma,
									addr);
			if (vpol)
				pol = vpol;
		} else if (vma->vm_policy)
			pol = vma->vm_policy;
	}
	if (!pol)
		pol = &default_policy;
	return pol;
}