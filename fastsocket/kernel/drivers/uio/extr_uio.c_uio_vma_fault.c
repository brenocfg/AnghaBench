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
struct vm_fault {int pgoff; struct page* page; } ;
struct vm_area_struct {struct uio_device* vm_private_data; } ;
struct uio_device {TYPE_2__* info; } ;
struct page {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mem; } ;
struct TYPE_3__ {scalar_t__ memtype; scalar_t__ addr; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ UIO_MEM_LOGICAL ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int uio_find_mem_index (struct vm_area_struct*) ; 
 struct page* virt_to_page (scalar_t__) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static int uio_vma_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct uio_device *idev = vma->vm_private_data;
	struct page *page;
	unsigned long offset;

	int mi = uio_find_mem_index(vma);
	if (mi < 0)
		return VM_FAULT_SIGBUS;

	/*
	 * We need to subtract mi because userspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	if (idev->info->mem[mi].memtype == UIO_MEM_LOGICAL)
		page = virt_to_page(idev->info->mem[mi].addr + offset);
	else
		page = vmalloc_to_page((void *)idev->info->mem[mi].addr
							+ offset);
	get_page(page);
	vmf->page = page;
	return 0;
}