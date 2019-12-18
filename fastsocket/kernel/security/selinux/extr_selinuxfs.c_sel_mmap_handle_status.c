#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; scalar_t__ vm_pgoff; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct file {struct page* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int EPERM ; 
 unsigned long PAGE_SIZE ; 
 int VM_MAYWRITE ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int remap_pfn_range (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sel_mmap_handle_status(struct file *filp,
				  struct vm_area_struct *vma)
{
	struct page    *status = filp->private_data;
	unsigned long	size = vma->vm_end - vma->vm_start;

	BUG_ON(!status);

	/* only allows one page from the head */
	if (vma->vm_pgoff > 0 || size != PAGE_SIZE)
		return -EIO;
	/* disallow writable mapping */
	if (vma->vm_flags & VM_WRITE)
		return -EPERM;
	/* disallow mprotect() turns it into writable */
	vma->vm_flags &= ~VM_MAYWRITE;

	return remap_pfn_range(vma, vma->vm_start,
			       page_to_pfn(status),
			       size, vma->vm_page_prot);
}