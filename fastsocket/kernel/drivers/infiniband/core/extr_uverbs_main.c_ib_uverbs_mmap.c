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
struct vm_area_struct {int dummy; } ;
struct ib_uverbs_file {int /*<<< orphan*/  ucontext; TYPE_2__* device; } ;
struct file {struct ib_uverbs_file* private_data; } ;
struct TYPE_4__ {TYPE_1__* ib_dev; } ;
struct TYPE_3__ {int (* mmap ) (int /*<<< orphan*/ ,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int ib_uverbs_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct ib_uverbs_file *file = filp->private_data;

	if (!file->ucontext)
		return -ENODEV;
	else
		return file->device->ib_dev->mmap(file->ucontext, vma);
}