#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_7__ {TYPE_1__ vm_set; } ;
struct vm_area_struct {int vm_flags; TYPE_2__ shared; } ;
struct TYPE_10__ {TYPE_4__* dentry; } ;
struct file {TYPE_5__ f_path; } ;
struct address_space {int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  i_mmap_writable; } ;
struct TYPE_9__ {TYPE_3__* d_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_writecount; } ;

/* Variables and functions */
 int VM_DENYWRITE ; 
 int VM_NONLINEAR ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_dcache_mmap_lock (struct address_space*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_unlock (struct address_space*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vma_prio_tree_remove (struct vm_area_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_shared_vm_struct(struct vm_area_struct *vma,
		struct file *file, struct address_space *mapping)
{
	if (vma->vm_flags & VM_DENYWRITE)
		atomic_inc(&file->f_path.dentry->d_inode->i_writecount);
	if (vma->vm_flags & VM_SHARED)
		mapping->i_mmap_writable--;

	flush_dcache_mmap_lock(mapping);
	if (unlikely(vma->vm_flags & VM_NONLINEAR))
		list_del_init(&vma->shared.vm_set.list);
	else
		vma_prio_tree_remove(vma, &mapping->i_mmap);
	flush_dcache_mmap_unlock(mapping);
}