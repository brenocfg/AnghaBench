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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; scalar_t__ vm_file; } ;
struct dma_buf {unsigned long size; TYPE_1__* ops; scalar_t__ file; } ;
struct TYPE_2__ {int (* mmap ) (struct dma_buf*,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  get_file (scalar_t__) ; 
 int stub1 (struct dma_buf*,struct vm_area_struct*) ; 

int dma_buf_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma,
		 unsigned long pgoff)
{
	if (WARN_ON(!dmabuf || !vma))
		return -EINVAL;

	/* check for offset overflow */
	if (pgoff + ((vma->vm_end - vma->vm_start) >> PAGE_SHIFT) < pgoff)
		return -EOVERFLOW;

	/* check for overflowing the buffer's size */
	if (pgoff + ((vma->vm_end - vma->vm_start) >> PAGE_SHIFT) >
	    dmabuf->size >> PAGE_SHIFT)
		return -EINVAL;

	/* readjust the vma */
	if (vma->vm_file)
		fput(vma->vm_file);

	vma->vm_file = dmabuf->file;
	get_file(vma->vm_file);

	vma->vm_pgoff = pgoff;

	return dmabuf->ops->mmap(dmabuf, vma);
}