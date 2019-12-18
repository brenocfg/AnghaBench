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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int /*<<< orphan*/ * vm_ops; TYPE_2__* vm_private_data; int /*<<< orphan*/  vm_flags; scalar_t__ vm_pgoff; } ;
struct file {scalar_t__ private_data; } ;
struct TYPE_3__ {unsigned long bufflen; int page_order; int k_use_sg; } ;
struct TYPE_4__ {int mmap_called; TYPE_1__ reserve; } ;
typedef  TYPE_1__ Sg_scatter_hold ;
typedef  TYPE_2__ Sg_fd ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SCSI_LOG_TIMEOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_RESERVED ; 
 int /*<<< orphan*/  printk (char*,void*,int) ; 
 int /*<<< orphan*/  sg_mmap_vm_ops ; 

__attribute__((used)) static int
sg_mmap(struct file *filp, struct vm_area_struct *vma)
{
	Sg_fd *sfp;
	unsigned long req_sz, len, sa;
	Sg_scatter_hold *rsv_schp;
	int k, length;

	if ((!filp) || (!vma) || (!(sfp = (Sg_fd *) filp->private_data)))
		return -ENXIO;
	req_sz = vma->vm_end - vma->vm_start;
	SCSI_LOG_TIMEOUT(3, printk("sg_mmap starting, vm_start=%p, len=%d\n",
				   (void *) vma->vm_start, (int) req_sz));
	if (vma->vm_pgoff)
		return -EINVAL;	/* want no offset */
	rsv_schp = &sfp->reserve;
	if (req_sz > rsv_schp->bufflen)
		return -ENOMEM;	/* cannot map more than reserved buffer */

	sa = vma->vm_start;
	length = 1 << (PAGE_SHIFT + rsv_schp->page_order);
	for (k = 0; k < rsv_schp->k_use_sg && sa < vma->vm_end; k++) {
		len = vma->vm_end - sa;
		len = (len < length) ? len : length;
		sa += len;
	}

	sfp->mmap_called = 1;
	vma->vm_flags |= VM_RESERVED;
	vma->vm_private_data = sfp;
	vma->vm_ops = &sg_mmap_vm_ops;
	return 0;
}