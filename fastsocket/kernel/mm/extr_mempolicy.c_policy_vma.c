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
struct vm_area_struct {struct mempolicy* vm_policy; TYPE_1__* vm_ops; int /*<<< orphan*/  vm_file; int /*<<< orphan*/  vm_pgoff; int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct mempolicy {int dummy; } ;
struct TYPE_2__ {int (* set_policy ) (struct vm_area_struct*,struct mempolicy*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mpol_get (struct mempolicy*) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int (*) (struct vm_area_struct*,struct mempolicy*)) ; 
 int stub1 (struct vm_area_struct*,struct mempolicy*) ; 

__attribute__((used)) static int policy_vma(struct vm_area_struct *vma, struct mempolicy *new)
{
	int err = 0;
	struct mempolicy *old = vma->vm_policy;

	pr_debug("vma %lx-%lx/%lx vm_ops %p vm_file %p set_policy %p\n",
		 vma->vm_start, vma->vm_end, vma->vm_pgoff,
		 vma->vm_ops, vma->vm_file,
		 vma->vm_ops ? vma->vm_ops->set_policy : NULL);

	if (vma->vm_ops && vma->vm_ops->set_policy)
		err = vma->vm_ops->set_policy(vma, new);
	if (!err) {
		mpol_get(new);
		vma->vm_policy = new;
		mpol_put(old);
	}
	return err;
}