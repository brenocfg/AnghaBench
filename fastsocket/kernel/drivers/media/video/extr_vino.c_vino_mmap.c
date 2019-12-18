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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; struct file* vm_file; struct vino_framebuffer* vm_private_data; int /*<<< orphan*/  vm_page_prot; } ;
struct TYPE_2__ {unsigned long page_count; scalar_t__* virtual; } ;
struct vino_framebuffer {unsigned long offset; int map_count; TYPE_1__ desc_table; } ;
struct vino_channel_settings {int /*<<< orphan*/  mutex; int /*<<< orphan*/  fb_queue; scalar_t__ reading; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_RESERVED ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct vino_channel_settings* video_drvdata (struct file*) ; 
 struct vino_framebuffer* vino_queue_get_buffer (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int vino_queue_get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino_vm_ops ; 
 unsigned long virt_to_phys (void*) ; 

__attribute__((used)) static int vino_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct vino_channel_settings *vcs = video_drvdata(file);

	unsigned long start = vma->vm_start;
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;

	struct vino_framebuffer *fb = NULL;
	unsigned int i, length;
	int ret = 0;

	dprintk("mmap():\n");

	// TODO: reject mmap if already mapped

	if (mutex_lock_interruptible(&vcs->mutex))
		return -EINTR;

	if (vcs->reading) {
		ret = -EBUSY;
		goto out;
	}

	// TODO: check queue type

	if (!(vma->vm_flags & VM_WRITE)) {
		dprintk("mmap(): app bug: PROT_WRITE please\n");
		ret = -EINVAL;
		goto out;
	}
	if (!(vma->vm_flags & VM_SHARED)) {
		dprintk("mmap(): app bug: MAP_SHARED please\n");
		ret = -EINVAL;
		goto out;
	}

	/* find the correct buffer using offset */
	length = vino_queue_get_length(&vcs->fb_queue);
	if (length == 0) {
		dprintk("mmap(): queue not initialized\n");
		ret = -EINVAL;
		goto out;
	}

	for (i = 0; i < length; i++) {
		fb = vino_queue_get_buffer(&vcs->fb_queue, i);
		if (fb == NULL) {
			dprintk("mmap(): vino_queue_get_buffer() failed\n");
			ret = -EINVAL;
			goto out;
		}

		if (fb->offset == offset)
			goto found;
	}

	dprintk("mmap(): invalid offset = %lu\n", offset);
	ret = -EINVAL;
	goto out;

found:
	dprintk("mmap(): buffer = %d\n", i);

	if (size > (fb->desc_table.page_count * PAGE_SIZE)) {
		dprintk("mmap(): failed: size = %lu > %lu\n",
			size, fb->desc_table.page_count * PAGE_SIZE);
		ret = -EINVAL;
		goto out;
	}

	for (i = 0; i < fb->desc_table.page_count; i++) {
		unsigned long pfn =
			virt_to_phys((void *)fb->desc_table.virtual[i]) >>
			PAGE_SHIFT;

		if (size < PAGE_SIZE)
			break;

		// protection was: PAGE_READONLY
		if (remap_pfn_range(vma, start, pfn, PAGE_SIZE,
				    vma->vm_page_prot)) {
			dprintk("mmap(): remap_pfn_range() failed\n");
			ret = -EAGAIN;
			goto out;
		}

		start += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	fb->map_count = 1;

	vma->vm_flags |= VM_DONTEXPAND | VM_RESERVED;
	vma->vm_flags &= ~VM_IO;
	vma->vm_private_data = fb;
	vma->vm_file = file;
	vma->vm_ops = &vino_vm_ops;

out:
	mutex_unlock(&vcs->mutex);

	return ret;
}