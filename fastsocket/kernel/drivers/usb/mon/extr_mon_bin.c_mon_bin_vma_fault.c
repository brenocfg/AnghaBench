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
struct vm_fault {unsigned long pgoff; struct page* page; } ;
struct vm_area_struct {struct mon_reader_bin* vm_private_data; } ;
struct page {int dummy; } ;
struct mon_reader_bin {unsigned long b_size; TYPE_1__* b_vec; } ;
struct TYPE_2__ {struct page* pg; } ;

/* Variables and functions */
 unsigned long CHUNK_SIZE ; 
 unsigned long PAGE_SHIFT ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  get_page (struct page*) ; 

__attribute__((used)) static int mon_bin_vma_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct mon_reader_bin *rp = vma->vm_private_data;
	unsigned long offset, chunk_idx;
	struct page *pageptr;

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= rp->b_size)
		return VM_FAULT_SIGBUS;
	chunk_idx = offset / CHUNK_SIZE;
	pageptr = rp->b_vec[chunk_idx].pg;
	get_page(pageptr);
	vmf->page = pageptr;
	return 0;
}