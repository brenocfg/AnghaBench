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
struct vm_area_struct {int vm_flags; struct file* vm_file; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  i_mmap_nonlinear; int /*<<< orphan*/  i_mmap_writable; } ;
struct TYPE_5__ {TYPE_1__* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_writecount; } ;

/* Variables and functions */
 int VM_DENYWRITE ; 
 int VM_NONLINEAR ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_dcache_mmap_lock (struct address_space*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_unlock (struct address_space*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vma_nonlinear_insert (struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vma_prio_tree_insert (struct vm_area_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vma_link_file(struct vm_area_struct *vma)
{
	struct file *file;

	file = vma->vm_file;
	if (file) {
		struct address_space *mapping = file->f_mapping;

		if (vma->vm_flags & VM_DENYWRITE)
			atomic_dec(&file->f_path.dentry->d_inode->i_writecount);
		if (vma->vm_flags & VM_SHARED)
			mapping->i_mmap_writable++;

		flush_dcache_mmap_lock(mapping);
		if (unlikely(vma->vm_flags & VM_NONLINEAR))
			vma_nonlinear_insert(vma, &mapping->i_mmap_nonlinear);
		else
			vma_prio_tree_insert(vma, &mapping->i_mmap);
		flush_dcache_mmap_unlock(mapping);
	}
}