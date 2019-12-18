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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct proc_dir_entry {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int page_map_mmap( struct file *file, struct vm_area_struct *vma )
{
	struct proc_dir_entry *dp = PDE(file->f_path.dentry->d_inode);

	if ((vma->vm_end - vma->vm_start) > dp->size)
		return -EINVAL;

	remap_pfn_range(vma, vma->vm_start, __pa(dp->data) >> PAGE_SHIFT,
						dp->size, vma->vm_page_prot);
	return 0;
}