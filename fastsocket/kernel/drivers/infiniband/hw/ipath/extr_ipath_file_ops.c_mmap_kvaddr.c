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
typedef  scalar_t__ u64 ;
struct vm_area_struct {int vm_flags; unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/ * vm_ops; } ;
struct ipath_portdata {unsigned int port_subport_cnt; size_t port_rcvegrbuf_chunks; size_t port_rcvegrbuf_size; size_t port_rcvhdrq_size; void* subport_rcvegrbuf; void* subport_rcvhdr_base; void* subport_uregbase; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  MM ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int VM_DONTEXPAND ; 
 int VM_MAYWRITE ; 
 int VM_RESERVED ; 
 int VM_WRITE ; 
 scalar_t__ cvt_kvaddr (void*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  ipath_file_vm_ops ; 

__attribute__((used)) static int mmap_kvaddr(struct vm_area_struct *vma, u64 pgaddr,
		       struct ipath_portdata *pd, unsigned subport)
{
	unsigned long len;
	struct ipath_devdata *dd;
	void *addr;
	size_t size;
	int ret = 0;

	/* If the port is not shared, all addresses should be physical */
	if (!pd->port_subport_cnt)
		goto bail;

	dd = pd->port_dd;
	size = pd->port_rcvegrbuf_chunks * pd->port_rcvegrbuf_size;

	/*
	 * Each process has all the subport uregbase, rcvhdrq, and
	 * rcvegrbufs mmapped - as an array for all the processes,
	 * and also separately for this process.
	 */
	if (pgaddr == cvt_kvaddr(pd->subport_uregbase)) {
		addr = pd->subport_uregbase;
		size = PAGE_SIZE * pd->port_subport_cnt;
	} else if (pgaddr == cvt_kvaddr(pd->subport_rcvhdr_base)) {
		addr = pd->subport_rcvhdr_base;
		size = pd->port_rcvhdrq_size * pd->port_subport_cnt;
	} else if (pgaddr == cvt_kvaddr(pd->subport_rcvegrbuf)) {
		addr = pd->subport_rcvegrbuf;
		size *= pd->port_subport_cnt;
        } else if (pgaddr == cvt_kvaddr(pd->subport_uregbase +
                                        PAGE_SIZE * subport)) {
                addr = pd->subport_uregbase + PAGE_SIZE * subport;
                size = PAGE_SIZE;
        } else if (pgaddr == cvt_kvaddr(pd->subport_rcvhdr_base +
                                pd->port_rcvhdrq_size * subport)) {
                addr = pd->subport_rcvhdr_base +
                        pd->port_rcvhdrq_size * subport;
                size = pd->port_rcvhdrq_size;
        } else if (pgaddr == cvt_kvaddr(pd->subport_rcvegrbuf +
                               size * subport)) {
                addr = pd->subport_rcvegrbuf + size * subport;
                /* rcvegrbufs are read-only on the slave */
                if (vma->vm_flags & VM_WRITE) {
                        dev_info(&dd->pcidev->dev,
                                 "Can't map eager buffers as "
                                 "writable (flags=%lx)\n", vma->vm_flags);
                        ret = -EPERM;
                        goto bail;
                }
                /*
                 * Don't allow permission to later change to writeable
                 * with mprotect.
                 */
                vma->vm_flags &= ~VM_MAYWRITE;
	} else {
		goto bail;
	}
	len = vma->vm_end - vma->vm_start;
	if (len > size) {
		ipath_cdbg(MM, "FAIL: reqlen %lx > %zx\n", len, size);
		ret = -EINVAL;
		goto bail;
	}

	vma->vm_pgoff = (unsigned long) addr >> PAGE_SHIFT;
	vma->vm_ops = &ipath_file_vm_ops;
	vma->vm_flags |= VM_RESERVED | VM_DONTEXPAND;
	ret = 1;

bail:
	return ret;
}