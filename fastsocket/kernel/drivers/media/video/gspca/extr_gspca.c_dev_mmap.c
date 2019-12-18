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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_pgoff; struct gspca_frame* vm_private_data; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_flags; } ;
struct page {int dummy; } ;
struct TYPE_3__ {int offset; } ;
struct TYPE_4__ {scalar_t__ memory; unsigned long length; TYPE_1__ m; } ;
struct gspca_frame {scalar_t__ data; TYPE_2__ v4l2_buf; } ;
struct gspca_dev {int nframes; int /*<<< orphan*/  queue_lock; struct gspca_frame* frame; struct file* capt_file; int /*<<< orphan*/  present; } ;
struct file {struct gspca_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int EINVAL ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VM_IO ; 
 int /*<<< orphan*/  gspca_vm_open (struct vm_area_struct*) ; 
 int /*<<< orphan*/  gspca_vm_ops ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,struct page*) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static int dev_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct gspca_dev *gspca_dev = file->private_data;
	struct gspca_frame *frame;
	struct page *page;
	unsigned long addr, start, size;
	int i, ret;

	start = vma->vm_start;
	size = vma->vm_end - vma->vm_start;
	PDEBUG(D_STREAM, "mmap start:%08x size:%d", (int) start, (int) size);

	if (mutex_lock_interruptible(&gspca_dev->queue_lock))
		return -ERESTARTSYS;
	if (!gspca_dev->present) {
		ret = -ENODEV;
		goto out;
	}
	if (gspca_dev->capt_file != file) {
		ret = -EINVAL;
		goto out;
	}

	frame = NULL;
	for (i = 0; i < gspca_dev->nframes; ++i) {
		if (gspca_dev->frame[i].v4l2_buf.memory != V4L2_MEMORY_MMAP) {
			PDEBUG(D_STREAM, "mmap bad memory type");
			break;
		}
		if ((gspca_dev->frame[i].v4l2_buf.m.offset >> PAGE_SHIFT)
						== vma->vm_pgoff) {
			frame = &gspca_dev->frame[i];
			break;
		}
	}
	if (frame == NULL) {
		PDEBUG(D_STREAM, "mmap no frame buffer found");
		ret = -EINVAL;
		goto out;
	}
	if (size != frame->v4l2_buf.length) {
		PDEBUG(D_STREAM, "mmap bad size");
		ret = -EINVAL;
		goto out;
	}

	/*
	 * - VM_IO marks the area as being a mmaped region for I/O to a
	 *   device. It also prevents the region from being core dumped.
	 */
	vma->vm_flags |= VM_IO;

	addr = (unsigned long) frame->data;
	while (size > 0) {
		page = vmalloc_to_page((void *) addr);
		ret = vm_insert_page(vma, start, page);
		if (ret < 0)
			goto out;
		start += PAGE_SIZE;
		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	vma->vm_ops = &gspca_vm_ops;
	vma->vm_private_data = frame;
	gspca_vm_open(vma);
	ret = 0;
out:
	mutex_unlock(&gspca_dev->queue_lock);
	return ret;
}