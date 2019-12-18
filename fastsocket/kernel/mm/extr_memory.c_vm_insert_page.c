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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_flags; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  VM_INSERTPAGE ; 
 int insert_page (struct vm_area_struct*,unsigned long,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 

int vm_insert_page(struct vm_area_struct *vma, unsigned long addr,
			struct page *page)
{
	if (addr < vma->vm_start || addr >= vma->vm_end)
		return -EFAULT;
	if (!page_count(page))
		return -EINVAL;
	vma->vm_flags |= VM_INSERTPAGE;
	return insert_page(vma, addr, page, vma->vm_page_prot);
}