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
struct vm_area_struct {int vm_flags; scalar_t__ vm_end; scalar_t__ vm_start; unsigned int vm_pgoff; TYPE_2__* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct go7007_file {unsigned int buf_count; int /*<<< orphan*/  lock; TYPE_2__* bufs; TYPE_1__* go; } ;
struct file {struct go7007_file* private_data; } ;
struct TYPE_4__ {int mapped; scalar_t__ user_addr; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 unsigned int GO7007_BUF_PAGES ; 
 scalar_t__ GO7007_BUF_SIZE ; 
 scalar_t__ STATUS_ONLINE ; 
 int VM_DONTEXPAND ; 
 int VM_IO ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  go7007_vm_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int go7007_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct go7007_file *gofh = file->private_data;
	unsigned int index;

	if (gofh->go->status != STATUS_ONLINE)
		return -EIO;
	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL; /* only support VM_SHARED mapping */
	if (vma->vm_end - vma->vm_start != GO7007_BUF_SIZE)
		return -EINVAL; /* must map exactly one full buffer */
	mutex_lock(&gofh->lock);
	index = vma->vm_pgoff / GO7007_BUF_PAGES;
	if (index >= gofh->buf_count) {
		mutex_unlock(&gofh->lock);
		return -EINVAL; /* trying to map beyond requested buffers */
	}
	if (index * GO7007_BUF_PAGES != vma->vm_pgoff) {
		mutex_unlock(&gofh->lock);
		return -EINVAL; /* offset is not aligned on buffer boundary */
	}
	if (gofh->bufs[index].mapped > 0) {
		mutex_unlock(&gofh->lock);
		return -EBUSY;
	}
	gofh->bufs[index].mapped = 1;
	gofh->bufs[index].user_addr = vma->vm_start;
	vma->vm_ops = &go7007_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_flags &= ~VM_IO;
	vma->vm_private_data = &gofh->bufs[index];
	mutex_unlock(&gofh->lock);
	return 0;
}