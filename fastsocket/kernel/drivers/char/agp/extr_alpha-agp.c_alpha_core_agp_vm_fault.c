#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {struct page* page; scalar_t__ virtual_address; } ;
struct vm_area_struct {unsigned long vm_start; } ;
struct page {int dummy; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_7__ {unsigned long bus_base; } ;
struct TYPE_8__ {TYPE_1__* ops; TYPE_2__ aperture; } ;
typedef  TYPE_3__ alpha_agp_info ;
struct TYPE_9__ {TYPE_3__* dev_private_data; } ;
struct TYPE_6__ {unsigned long (* translate ) (TYPE_3__*,unsigned long) ;} ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __va (unsigned long) ; 
 TYPE_5__* agp_bridge ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned long stub1 (TYPE_3__*,unsigned long) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alpha_core_agp_vm_fault(struct vm_area_struct *vma,
					struct vm_fault *vmf)
{
	alpha_agp_info *agp = agp_bridge->dev_private_data;
	dma_addr_t dma_addr;
	unsigned long pa;
	struct page *page;

	dma_addr = (unsigned long)vmf->virtual_address - vma->vm_start
						+ agp->aperture.bus_base;
	pa = agp->ops->translate(agp, dma_addr);

	if (pa == (unsigned long)-EINVAL)
		return VM_FAULT_SIGBUS;	/* no translation */

	/*
	 * Get the page, inc the use count, and return it
	 */
	page = virt_to_page(__va(pa));
	get_page(page);
	vmf->page = page;
	return 0;
}