#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_2__* vm_region; TYPE_3__* vm_file; } ;
struct TYPE_6__ {TYPE_1__* f_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_top; } ;
struct TYPE_4__ {int (* mmap ) (TYPE_3__*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSYS ; 
 int stub1 (TYPE_3__*,struct vm_area_struct*) ; 

__attribute__((used)) static int do_mmap_shared_file(struct vm_area_struct *vma)
{
	int ret;

	ret = vma->vm_file->f_op->mmap(vma->vm_file, vma);
	if (ret == 0) {
		vma->vm_region->vm_top = vma->vm_region->vm_end;
		return 0;
	}
	if (ret != -ENOSYS)
		return ret;

	/* getting an ENOSYS error indicates that direct mmap isn't
	 * possible (as opposed to tried but failed) so we'll fall
	 * through to making a private copy of the data and mapping
	 * that if we can */
	return -ENODEV;
}