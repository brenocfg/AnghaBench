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
struct vma_data {unsigned long* maddr; scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct vm_fault {size_t pgoff; scalar_t__ virtual_address; } ;
struct vm_area_struct {struct vma_data* vm_private_data; } ;
typedef  size_t pgoff_t ;

/* Variables and functions */
 scalar_t__ MSPEC_FETCHOP ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long TO_AMO (unsigned long) ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_OOM ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 int /*<<< orphan*/  numa_node_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned long uncached_alloc_page (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uncached_free_page (unsigned long,int) ; 
 int /*<<< orphan*/  vm_insert_pfn (struct vm_area_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static int
mspec_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	unsigned long paddr, maddr;
	unsigned long pfn;
	pgoff_t index = vmf->pgoff;
	struct vma_data *vdata = vma->vm_private_data;

	maddr = (volatile unsigned long) vdata->maddr[index];
	if (maddr == 0) {
		maddr = uncached_alloc_page(numa_node_id(), 1);
		if (maddr == 0)
			return VM_FAULT_OOM;

		spin_lock(&vdata->lock);
		if (vdata->maddr[index] == 0) {
			vdata->count++;
			vdata->maddr[index] = maddr;
		} else {
			uncached_free_page(maddr, 1);
			maddr = vdata->maddr[index];
		}
		spin_unlock(&vdata->lock);
	}

	if (vdata->type == MSPEC_FETCHOP)
		paddr = TO_AMO(maddr);
	else
		paddr = maddr & ~__IA64_UNCACHED_OFFSET;

	pfn = paddr >> PAGE_SHIFT;

	/*
	 * vm_insert_pfn can fail with -EBUSY, but in that case it will
	 * be because another thread has installed the pte first, so it
	 * is no problem.
	 */
	vm_insert_pfn(vma, (unsigned long)vmf->virtual_address, pfn);

	return VM_FAULT_NOPAGE;
}