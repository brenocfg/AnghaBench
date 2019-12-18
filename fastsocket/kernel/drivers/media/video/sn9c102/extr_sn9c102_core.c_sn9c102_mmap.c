#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; int vm_pgoff; TYPE_3__* vm_private_data; int /*<<< orphan*/ * vm_ops; } ;
struct sn9c102_device {int state; scalar_t__ io; size_t nbuffers; int /*<<< orphan*/  fileop_mutex; TYPE_3__* frame; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int offset; } ;
struct TYPE_5__ {TYPE_1__ m; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {void* bufmem; TYPE_2__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int DEV_DISCONNECTED ; 
 int DEV_MISCONFIGURED ; 
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 scalar_t__ IO_MMAP ; 
 unsigned long PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_IO ; 
 int VM_READ ; 
 int VM_RESERVED ; 
 int VM_WRITE ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn9c102_vm_open (struct vm_area_struct*) ; 
 int /*<<< orphan*/  sn9c102_vm_ops ; 
 struct sn9c102_device* video_drvdata (struct file*) ; 
 scalar_t__ vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

__attribute__((used)) static int sn9c102_mmap(struct file* filp, struct vm_area_struct *vma)
{
	struct sn9c102_device *cam = video_drvdata(filp);
	unsigned long size = vma->vm_end - vma->vm_start,
		      start = vma->vm_start;
	void *pos;
	u32 i;

	if (mutex_lock_interruptible(&cam->fileop_mutex))
		return -ERESTARTSYS;

	if (cam->state & DEV_DISCONNECTED) {
		DBG(1, "Device not present");
		mutex_unlock(&cam->fileop_mutex);
		return -ENODEV;
	}

	if (cam->state & DEV_MISCONFIGURED) {
		DBG(1, "The camera is misconfigured. Close and open it "
		       "again.");
		mutex_unlock(&cam->fileop_mutex);
		return -EIO;
	}

	if (!(vma->vm_flags & (VM_WRITE | VM_READ))) {
		mutex_unlock(&cam->fileop_mutex);
		return -EACCES;
	}

	if (cam->io != IO_MMAP ||
	    size != PAGE_ALIGN(cam->frame[0].buf.length)) {
		mutex_unlock(&cam->fileop_mutex);
		return -EINVAL;
	}

	for (i = 0; i < cam->nbuffers; i++) {
		if ((cam->frame[i].buf.m.offset>>PAGE_SHIFT) == vma->vm_pgoff)
			break;
	}
	if (i == cam->nbuffers) {
		mutex_unlock(&cam->fileop_mutex);
		return -EINVAL;
	}

	vma->vm_flags |= VM_IO;
	vma->vm_flags |= VM_RESERVED;

	pos = cam->frame[i].bufmem;
	while (size > 0) { /* size is page-aligned */
		if (vm_insert_page(vma, start, vmalloc_to_page(pos))) {
			mutex_unlock(&cam->fileop_mutex);
			return -EAGAIN;
		}
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	vma->vm_ops = &sn9c102_vm_ops;
	vma->vm_private_data = &cam->frame[i];
	sn9c102_vm_open(vma);

	mutex_unlock(&cam->fileop_mutex);

	return 0;
}