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
struct vm_area_struct {int vm_flags; int vm_pgoff; int /*<<< orphan*/  vm_mm; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/ * vm_ops; } ;
struct inode {int i_size; int /*<<< orphan*/  i_mutex; } ;
struct hstate {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int VM_HUGETLB ; 
 int VM_RESERVED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 struct hstate* hstate_file (struct file*) ; 
 int huge_page_mask (struct hstate*) ; 
 int huge_page_order (struct hstate*) ; 
 int huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/  hugetlb_prefault_arch_hook (int /*<<< orphan*/ ) ; 
 scalar_t__ hugetlb_reserve_pages (struct inode*,int,int,struct vm_area_struct*,int) ; 
 int /*<<< orphan*/  hugetlb_vm_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hugetlbfs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	loff_t len, vma_len;
	int ret;
	struct hstate *h = hstate_file(file);

	/*
	 * vma address alignment (but not the pgoff alignment) has
	 * already been checked by prepare_hugepage_range.  If you add
	 * any error returns here, do so after setting VM_HUGETLB, so
	 * is_vm_hugetlb_page tests below unmap_region go the right
	 * way when do_mmap_pgoff unwinds (may be important on powerpc
	 * and ia64).
	 */
	vma->vm_flags |= VM_HUGETLB | VM_RESERVED;
	vma->vm_ops = &hugetlb_vm_ops;

	if (vma->vm_pgoff & ~(huge_page_mask(h) >> PAGE_SHIFT))
		return -EINVAL;

	vma_len = (loff_t)(vma->vm_end - vma->vm_start);

	mutex_lock(&inode->i_mutex);
	file_accessed(file);

	ret = -ENOMEM;
	len = vma_len + ((loff_t)vma->vm_pgoff << PAGE_SHIFT);

	if (hugetlb_reserve_pages(inode,
				vma->vm_pgoff >> huge_page_order(h),
				len >> huge_page_shift(h), vma,
				vma->vm_flags))
		goto out;

	ret = 0;
	hugetlb_prefault_arch_hook(vma->vm_mm);
	if (vma->vm_flags & VM_WRITE && inode->i_size < len)
		inode->i_size = len;
out:
	mutex_unlock(&inode->i_mutex);

	return ret;
}